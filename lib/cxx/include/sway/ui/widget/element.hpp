#ifndef SWAY_UI_WIDGETS_ELEMENT_HPP
#define SWAY_UI_WIDGETS_ELEMENT_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ui/widget/area.hpp>
#include <sway/ui/widget/areas/boxarea.hpp>
#include <sway/ui/widget/areas/contentarea.hpp>
#include <sway/ui/widget/areatypes.hpp>
#include <sway/ui/widget/types.hpp>

#include <array>
#include <memory>
#include <optional>
#include <type_traits>
#include <utility>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

class Element : public AreaHolder_t {
public:
#pragma region "Ctors/Dtor"

  // clang-format off
  Element(const math::sizef_t &size = math::size2f_one)
      : AreaHolder_t({
          std::make_shared<BoxArea>(AreaType::IDX_MRG),
          std::make_shared<BoxArea>(AreaType::IDX_BRD),
          std::make_shared<BoxArea>(AreaType::IDX_PAD),
          std::make_shared<ContentArea>()
        }) {}
  // clang-format on

  ~Element() = default;

#pragma endregion

  auto getAreaIndex(AreaType type) const -> i32_t {
    for (auto i = 0; i < this->size(); i++) {
      if (this->at(i)->type() == type) {
        return i;
      }
    }

    return GLOB_IDX_INVALID;
  }

  template <AreaType TYPE>
  auto getAreaIndex() const -> i32_t {
    return getAreaIndex(TYPE);
  }

  auto getArea(AreaType type) const -> std::optional<Area::SharedPtr_t> {
    const auto idx = getAreaIndex(type);
    // clang-format off
    return (idx != GLOB_IDX_INVALID) 
        ? std::optional<Area::SharedPtr_t>(this->at(idx)) 
        : std::nullopt;
    // clang-format on
  }

  template <AreaType TYPE, typename OUT = OutputAreaType_t<TYPE>>
  auto getArea() const -> std::optional<std::shared_ptr<OUT>> {
    const auto idx = getAreaIndex<TYPE>();
    // clang-format off
    return (idx != GLOB_IDX_INVALID) 
        ? std::optional<std::shared_ptr<OUT>>(std::static_pointer_cast<OUT>(this->at(idx))) 
        : std::nullopt;
    // clang-format on
  }

  template <AreaType TYPE, math::RectEdge EDGE>
  void setEdge(f32_t size) {
    auto area = getArea<TYPE>();
    if (!area.has_value()) {
      return;
    }

    area.value()->set(EDGE, size);
  }

  template <math::RectEdge EDGE>
  auto getEdge(std::optional<BoxArea::SharedPtr_t> area) const -> f32_t {
    return area.value()->at(EDGE);
  }

  template <math::RectEdge EDGE>
  auto getEdge(Area::SharedPtr_t area) const -> f32_t {
    return std::static_pointer_cast<BoxArea>(area)->at(EDGE);
  }

  template <AreaType TYPE, math::RectEdge EDGE>
  auto getEdge() const -> f32_t {
    auto area = getArea<TYPE>();
    if (!area.has_value()) {
      return 0.0F;
    }

    return getEdge<EDGE>(area);
  }

  template <AreaType TYPE>
  auto getPosition() const -> math::vec2f_t {
    auto result = math::vec2f_zero;
    for (auto i = 0; i < core::detail::toBase(TYPE); i++) {
      if (i == core::detail::toBase(AreaType::IDX_CNT)) {
        continue;
      }

      const auto type = core::detail::toEnum<AreaType>(i);
      auto area = getArea(type);
      if (!area.has_value()) {
        // TODO:
      } else {
        auto val = area.value();
        result += math::vec2f_t(getEdge<math::RectEdge::IDX_L>(val), getEdge<math::RectEdge::IDX_T>(val));
      }
    }

    return result;
  }

  template <AreaType TYPE>
  auto getSize() const -> math::size2f_t {
    auto result = getContentSize();
    for (auto i = core::detail::toBase(AreaType::IDX_PAD); i >= core::detail::toBase(TYPE); i--) {
      const auto type = core::detail::toEnum<AreaType>(i);
      auto area = getArea(type);
      if (!area.has_value()) {
        // TODO:
      } else {
        auto val = area.value();
        result += math::vec2f_t(getEdge<math::RectEdge::IDX_L>(val) + getEdge<math::RectEdge::IDX_R>(val),
            getEdge<math::RectEdge::IDX_T>(val) + getEdge<math::RectEdge::IDX_B>(val));
      }
    }

    return result;
  }

  [[nodiscard]]
  auto getContentSize() const -> math::size2f_t {
    auto result = math::size2f_zero;
    auto cnt = getArea<AreaType::IDX_CNT>();
    if (!cnt.has_value()) {
      return result;
    } else {
      result = cnt.value()->getSize();
    }

    return result;
  }

  [[nodiscard]]
  auto getInnerSize() const -> math::size2f_t {
    return getSize<AreaType::IDX_PAD>();
  }

  [[nodiscard]]
  auto getOuterSize() const -> math::size2f_t {
    return getSize<AreaType::IDX_BRD>();
  }

  [[nodiscard]]
  auto getOuterSizeWithMargin() const -> math::size2f_t {
    return getSize<AreaType::IDX_MRG>();
  }

private:
  math::rect4f_t rect_;
};

NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGETS_ELEMENT_HPP
