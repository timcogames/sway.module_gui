#include <sway/ui/widget/element.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

Element::Element()
    : position_(ElementPosition::RELATIVE)
    , offset_(math::point2f_zero)
    , offsetDirty_(false) {}

void Element::setPosition(ElementPosition pos) { position_ = pos; }

auto Element::getPosition() const -> ElementPosition { return position_; }

void Element::setOffset(const math::point2f_t &pnt) {
  offset_ = pnt;
  offsetDirty_ = true;
}

void Element::setOffset(f32_t x, f32_t y) { setOffset({x, y}); }

auto Element::getOffset(ElementPosition pos) const -> math::point2f_t {
  if (position_ == ElementPosition::RELATIVE) {
  } else if (position_ == ElementPosition::ABSOLUTE || position_ == ElementPosition::FIXED) {
  }

  return offset_;
}

auto Element::isOffsetDirty() const -> bool { return offsetDirty_; }

void Element::updateOffset() {
  auto parentOpt = this->getParentNode();
  if (!parentOpt.has_value()) {
    return;
  }

  auto parent = std::static_pointer_cast<Element>(parentOpt.value());

  if (position_ == ElementPosition::RELATIVE) {
    auto parentContentSize = parent->getAreaHolder().getContentSize();
    offset_ = math::point2f_zero;
  } else if (position_ == ElementPosition::ABSOLUTE || position_ == ElementPosition::FIXED) {
    auto parentContentSize = getInnerSize();
    offset_ = math::point2f_zero;
  } else {
    offset_ = math::point2f_zero;
  }

  offsetDirty_ = false;
}

auto Element::getAreaHolder() const -> ElementAreaHolder { return holder_; }

auto Element::getInnerSize() const -> math::size2f_t { return holder_.getSize<AreaType::IDX_PAD>(); }

auto Element::getOuterSize() const -> math::size2f_t { return holder_.getSize<AreaType::IDX_BRD>(); }

auto Element::getOuterSizeWithMargin() const -> math::size2f_t { return holder_.getSize<AreaType::IDX_MRG>(); }

NAMESPACE_END(ui)
NAMESPACE_END(sway)
