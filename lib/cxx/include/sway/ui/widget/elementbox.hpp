#ifndef SWAY_UI_WIDGET_ELEMENTBOX_HPP
#define SWAY_UI_WIDGET_ELEMENTBOX_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>

#include <array>
#include <memory>
#include <optional>
#include <utility>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

using AreaSharedPtr_t = std::shared_ptr<math::Area<f32_t>>;
using AreaContainer_t = std::array<AreaSharedPtr_t, NUM_OF_AREAS>;

template <auto TYPE>
struct IsContentArea : public std::false_type {};

template <>
struct IsContentArea<math::AreaType::CNT> : public std::true_type {};

class ElementBox : public AreaContainer_t {
public:
#pragma region "Ctors/Dtor"

  // clang-format off
  ElementBox(const math::sizef_t &size = math::size2f_one)
      : AreaContainer_t({
          std::make_shared<math::Area<f32_t>>(math::AreaType::MRG),
          std::make_shared<math::Area<f32_t>>(math::AreaType::BRD),
          std::make_shared<math::Area<f32_t>>(math::AreaType::PAD),
          std::make_shared<math::Area<f32_t>>(math::AreaType::CNT)
        }) {
    getArea<math::AreaType::CNT>().value()->setContent(size);
  }
  // clang-format on

  ~ElementBox() = default;

#pragma endregion

  template <math::AreaType TYPE>
  auto getAreaIndex() const -> i32_t {
    for (auto i = 0; i < this->size(); i++) {
      if (this->at(i)->type() == TYPE) {
        return i;
      }
    }

    return GLOB_IDX_INVALID;
  }

  template <math::AreaType TYPE>
  auto getArea() const -> std::optional<AreaSharedPtr_t> {
    const auto idx = getAreaIndex<TYPE>();
    // clang-format off
    return (idx != GLOB_IDX_INVALID) 
        ? std::optional<AreaSharedPtr_t>(this->at(idx)) 
        : std::nullopt;
    // clang-format on
  }

  template <math::AreaType TYPE, math::RectEdge EDGE,
      typename = typename std::enable_if<!IsContentArea<TYPE>::value, math::AreaType>::type>
  void setEdge(f32_t size) {
    auto area = getArea<TYPE>();
    if (!area.has_value()) {
      return;
    }

    area.value()->at(EDGE) = size;
  }

  template <math::RectEdge EDGE>
  auto getEdge(std::optional<AreaSharedPtr_t> area) const -> f32_t {
    return area.value()->at(EDGE);
  }

  template <math::AreaType TYPE, math::RectEdge EDGE>
  auto getEdge() const -> f32_t {
    auto area = getArea<TYPE>();
    if (!area.has_value()) {
      return 0.0F;
    }

    return getEdge<EDGE>(area);
  }

  template <math::AreaType TYPE>
  auto getPosition() const -> math::vec2f_t {
    auto result = math::vec2f_zero;

    if (TYPE == math::AreaType::BRD || TYPE == math::AreaType::PAD || TYPE == math::AreaType::CNT) {
      auto mgn = getArea<math::AreaType::MRG>();
      if (!mgn.has_value()) {
        // TODO:
      } else {
        result += math::vec2f_t(getEdge<math::RectEdge::IDX_L>(mgn), getEdge<math::RectEdge::IDX_T>(mgn));
      }
    }

    if (TYPE == math::AreaType::PAD || TYPE == math::AreaType::CNT) {
      auto brd = getArea<math::AreaType::BRD>();
      if (!brd.has_value()) {
        // TODO:
      } else {
        result = math::vec2f_t(
            result.getX() + getEdge<math::RectEdge::IDX_L>(brd), result.getY() + getEdge<math::RectEdge::IDX_T>(brd));
      }
    }

    if (TYPE == math::AreaType::CNT) {
      auto pad = getArea<math::AreaType::PAD>();
      if (!pad.has_value()) {
        // TODO:
      } else {
        result = math::vec2f_t(
            result.getX() + getEdge<math::RectEdge::IDX_L>(pad), result.getY() + getEdge<math::RectEdge::IDX_T>(pad));
      }
    }

    return result;
  }

  template <math::AreaType TYPE>
  auto getSize() const -> math::size2f_t {
    auto result = math::size2f_zero;

    auto cnt = getArea<math::AreaType::CNT>();
    if (!cnt.has_value()) {
      return result;
    } else {
      result = cnt.value()->getContent();
    }

    if (TYPE == math::AreaType::PAD) {
      auto pad = getArea<math::AreaType::PAD>();
      if (!pad.has_value()) {
        // TODO:
      } else {
        result = math::vec2f_t(
            result.getW() + getEdge<math::RectEdge::IDX_L>(pad), result.getH() + getEdge<math::RectEdge::IDX_T>(pad));
      }
    }

    return result;
  }
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_ELEMENTBOX_HPP
