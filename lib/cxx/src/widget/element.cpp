#include <sway/ui/widget/element.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

Element::Element()
    : position_(ElementPosition::RELATIVE) {
  this->subscribe(this, "NodeAdded", EVENT_HANDLER(Element, handleAddNode));
}

void Element::setPosition(ElementPosition pos) { position_ = pos; }

auto Element::getPosition() const -> ElementPosition { return position_; }

void Element::setOffset(const math::point2f_t &pnt) {
  offset_.original = pnt;
  offset_.dirty = true;

  // recursiveUpdate(this->getSharedFrom<Element>(this));
}

void Element::setOffset(f32_t x, f32_t y) { setOffset(math::point2f_t(x, y)); }

auto Element::getOffset() const -> math::point2f_t { return offset_.computed; }

auto Element::isOffsetDirty() const -> bool { return offset_.dirty; }

void Element::updateOffset() {
  if (position_ == ElementPosition::RELATIVE) {
    auto parentOpt = this->getParentNode();
    if (!parentOpt.has_value()) {
      return;
    }

    auto parent = std::static_pointer_cast<Element>(parentOpt.value());

    auto parentOffset = parent->getOffset();
    auto parentAreaPosition = parent->getAreaHolder().getPosition<ui::AreaType::IDX_CNT>();
    auto parentAreaSize = parent->getAreaHolder().getContentSize();
    offset_.computed = math::point2f_t(parentOffset.getX(), parentOffset.getY());
  } else if (position_ == ElementPosition::ABSOLUTE || position_ == ElementPosition::FIXED) {
    // auto parentInnerSize = parent->getInnerSize();
    offset_.computed = offset_.original;
  } else {
    offset_.computed = offset_.original;
  }

  offset_.dirty = false;
}

void Element::recursiveUpdate(Element::SharedPtr_t elem) {
  std::static_pointer_cast<Element>(elem)->updateOffset();

  for (const auto &item : elem->getChildNodes()) {
    recursiveUpdate(std::static_pointer_cast<Element>(item));
  }
}

auto Element::getAreaHolder() const -> ElementAreaHolder { return holder_; }

auto Element::getInnerSize() const -> math::size2f_t { return holder_.getSize<AreaType::IDX_PAD>(); }

auto Element::getOuterSize() const -> math::size2f_t { return holder_.getSize<AreaType::IDX_BRD>(); }

auto Element::getOuterSizeWithMargin() const -> math::size2f_t { return holder_.getSize<AreaType::IDX_MRG>(); }

void Element::handleAddNode(core::foundation::Event::Ptr_t evt) {
  auto evtdata = static_cast<core::container::NodeEventData *>(evt->data());
  recursiveUpdate(std::static_pointer_cast<Element>(this->getChildNode(evtdata->nodeidx)));
}

NAMESPACE_END(ui)
NAMESPACE_END(sway)
