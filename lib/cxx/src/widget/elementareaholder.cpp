#include <sway/ui/widget/areas/boxarea.hpp>
#include <sway/ui/widget/areas/contentarea.hpp>
#include <sway/ui/widget/elementareaholder.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

// clang-format off
ElementAreaHolder::ElementAreaHolder()
    : AreaHolder_t({
        std::make_shared<BoxArea>(AreaType::IDX_MRG),
        std::make_shared<BoxArea>(AreaType::IDX_BRD),
        std::make_shared<BoxArea>(AreaType::IDX_PAD),
        std::make_shared<ContentArea>()
    }) {}
// clang-format on

auto ElementAreaHolder::getAreaIndex(AreaType type) const -> i32_t {
  for (auto i = 0; i < this->size(); i++) {
    if (this->at(i)->type() == type) {
      return i;
    }
  }

  return GLOB_IDX_INVALID;
}

auto ElementAreaHolder::getArea(AreaType type) const -> std::optional<Area::SharedPtr_t> {
  const auto idx = getAreaIndex(type);
  // clang-format off
  return (idx != GLOB_IDX_INVALID) 
      ? std::optional<Area::SharedPtr_t>(this->at(idx)) 
      : std::nullopt;
  // clang-format on
}

auto ElementAreaHolder::getContentSize() const -> math::size2f_t {
  auto cnt = getArea<AreaType::IDX_CNT>();
  if (!cnt.has_value()) {
    return math::size2f_zero;
  }

  return cnt.value()->getSize();
}

NAMESPACE_END(ui)
NAMESPACE_END(sway)
