#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ui/area/_typedefs.hpp>
#include <sway/ui/area/areaholder.hpp>
#include <sway/ui/area/areatypes.hpp>
#include <sway/ui/area/specs/boxarea.hpp>
#include <sway/ui/area/specs/contentarea.hpp>

#include <memory>
#include <optional>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

template <AreaType TYPE>
auto AreaHolder::getAreaIndex() const -> i32_t {
  return getAreaIndex(TYPE);
}

template <AreaType TYPE, typename OUT>
auto AreaHolder::getArea() const -> std::optional<std::shared_ptr<OUT>> {
  const auto idx = getAreaIndex<TYPE>();
  // clang-format off
    return (idx != GLOB_IDX_INVALID)
        ? std::optional<std::shared_ptr<OUT>>(std::static_pointer_cast<OUT>(this->at(idx)))
        : std::nullopt;
  // clang-format on
}

template <AreaType TYPE, math::RectEdge::Enum EDGE>
void AreaHolder::setEdge(f32_t size) {
  auto area = getArea<TYPE>();
  if (!area.has_value()) {
    return;
  }

  area.value()->set(EDGE, size);
}

// template <math::RectEdge::Enum EDGE>
// auto AreaHolder::getEdge(AreaTypedefs::OptionalSharedPtr_t area) const -> f32_t {
//   return area.value()->at(EDGE);
// }

template <math::RectEdge::Enum EDGE>
auto AreaHolder::getEdge(AreaTypedefs::SharedPtr_t area) const -> f32_t {
  return std::static_pointer_cast<BoxArea>(area)->at(EDGE);
}

template <AreaType TYPE, math::RectEdge::Enum EDGE>
auto AreaHolder::getEdge() const -> f32_t {
  auto area = getArea<TYPE>();
  if (!area.has_value()) {
    return 0.0F;
  }

  return getEdge<EDGE>(area);
}

template <AreaType TYPE>
auto AreaHolder::getPosition() const -> math::vec2f_t {
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
      result += math::vec2f_t(getEdge<math::RectEdge::Enum::IDX_L>(val), getEdge<math::RectEdge::Enum::IDX_T>(val));
    }
  }

  return result;
}

template <AreaType TYPE>
auto AreaHolder::getSize() const -> math::size2f_t {
  auto result = getContentSize();
  for (auto i = core::detail::toBase(AreaType::IDX_PAD); i >= core::detail::toBase(TYPE); i--) {
    const auto type = core::detail::toEnum<AreaType>(i);
    auto area = getArea(type);
    if (!area.has_value()) {
      // TODO:
    } else {
      auto val = area.value();
      result += math::vec2f_t(getEdge<math::RectEdge::Enum::IDX_L>(val) + getEdge<math::RectEdge::Enum::IDX_R>(val),
          getEdge<math::RectEdge::Enum::IDX_T>(val) + getEdge<math::RectEdge::Enum::IDX_B>(val));
    }
  }

  return result;
}

NS_END()  // namespace ui
NS_END()  // namespace sway
