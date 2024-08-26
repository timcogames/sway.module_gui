#include <sway/ui/widget/element.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

Element::Element()
    : position_(ElementPosition::RELATIVE)
    , offset_(math::point2f_zero)
    , offsetDirty_(true) {}

void Element::setOffset(const math::point2f_t &pnt) {
  offset_ = pnt;
  offsetDirty_ = true;
}

auto Element::getOffset(ElementPosition pos) -> math::point2f_t {
  if (position_ == ElementPosition::RELATIVE) {
  } else if (position_ == ElementPosition::ABSOLUTE || position_ == ElementPosition::FIXED) {
  }
}

void Element::updateOffset() {
  auto parentOpt = this->getParentNode();
  if (!parentOpt.has_value()) {
    return;
  }

  auto parent = std::static_pointer_cast<Element>(parentOpt.value());

  if (position_ == ElementPosition::ABSOLUTE || position_ == ElementPosition::FIXED) {
  } else {
  }
}

NAMESPACE_END(ui)
NAMESPACE_END(sway)
