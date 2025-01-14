#include <sway/ui/area/areaholder.hpp>
#include <sway/ui/area/specs/boxarea.hpp>
#include <sway/ui/area/specs/contentarea.hpp>

namespace sway::ui {

// clang-format off
AreaHolder::AreaHolder()
    : AreaContainer_t({
        std::make_shared<BoxArea>(AreaType::IDX_MRG),
        std::make_shared<BoxArea>(AreaType::IDX_BRD),
        std::make_shared<BoxArea>(AreaType::IDX_PAD),
        std::make_shared<ContentArea>()
    }) {}
// clang-format on

auto AreaHolder::getAreaIndex(AreaType type) const -> i32_t {
  for (auto i = 0; i < this->size(); i++) {
    if (this->at(i)->getType() == type) {
      return i;
    }
  }

  return GLOB_IDX_INVALID;
}

auto AreaHolder::getArea(AreaType type) const -> AreaOptionalSharedPtr_t {
  const auto idx = getAreaIndex(type);
  // clang-format off
  return (idx != GLOB_IDX_INVALID) 
      ? AreaOptionalSharedPtr_t(this->at(idx)) 
      : std::nullopt;
  // clang-format on
}

auto AreaHolder::getContentSize() const -> math::size2f_t {
  auto cnt = getArea<AreaType::IDX_CNT>();
  if (!cnt.has_value()) {
    return math::size2f_zero;
  }

  return cnt.value()->getSize();
}

}  // namespace sway::ui
