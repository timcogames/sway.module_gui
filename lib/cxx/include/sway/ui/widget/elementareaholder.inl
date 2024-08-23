#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ui/widget/areas/boxarea.hpp>
#include <sway/ui/widget/areas/contentarea.hpp>
#include <sway/ui/widget/areatypes.hpp>
#include <sway/ui/widget/elementareaholder.hpp>
#include <sway/ui/widget/types.hpp>

#include <memory>
#include <optional>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

template <AreaType TYPE>
auto ElementAreaHolder::getAreaIndex() const -> i32_t {
  return getAreaIndex(TYPE);
}

template <AreaType TYPE, typename OUT>
auto ElementAreaHolder::getArea() const -> std::optional<std::shared_ptr<OUT>> {
  const auto idx = getAreaIndex<TYPE>();
  // clang-format off
    return (idx != GLOB_IDX_INVALID)
        ? std::optional<std::shared_ptr<OUT>>(std::static_pointer_cast<OUT>(this->at(idx)))
        : std::nullopt;
  // clang-format on
}

template <AreaType TYPE, math::RectEdge EDGE>
void ElementAreaHolder::setEdge(f32_t size) {
  auto area = getArea<TYPE>();
  if (!area.has_value()) {
    return;
  }

  area.value()->set(EDGE, size);
}

// template <math::RectEdge EDGE>
// auto ElementAreaHolder::getEdge(std::optional<BoxArea::SharedPtr_t> area) const -> f32_t {
//   return area.value()->at(EDGE);
// }

template <math::RectEdge EDGE>
auto ElementAreaHolder::getEdge(Area::SharedPtr_t area) const -> f32_t {
  return std::static_pointer_cast<BoxArea>(area)->at(EDGE);
}

template <AreaType TYPE, math::RectEdge EDGE>
auto ElementAreaHolder::getEdge() const -> f32_t {
  auto area = getArea<TYPE>();
  if (!area.has_value()) {
    return 0.0F;
  }

  return getEdge<EDGE>(area);
}

template <AreaType TYPE>
auto ElementAreaHolder::getPosition() const -> math::vec2f_t {
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
auto ElementAreaHolder::getSize() const -> math::size2f_t {
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

NAMESPACE_END(ui)
NAMESPACE_END(sway)
