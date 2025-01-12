#include <sway/ui/element/element.hpp>

namespace sway::ui {

Element::Element()
    : position_(ElementPosition::RELATIVE)
    , alignment_(math::Alignment::LEFT_TOP) {
  this->subscribe(this, "NodeAdded", EVENT_HANDLER(Element, handleAddNode));
}

void Element::setPosition(ElementPosition pos) { position_ = pos; }

auto Element::getPosition() const -> ElementPosition { return position_; }

void Element::setSize(const math::size2f_t &size) {
  this->getAreaHolder().getArea<AreaType::IDX_CNT>().value()->setSize(size);
}

void Element::setSize(f32_t wdt, f32_t hgt) { setSize(math::size2f_t(wdt, hgt)); }

auto Element::getSize() const -> math::size2f_t {
  return this->getAreaHolder().getArea<AreaType::IDX_CNT>().value()->getSize();
}

void Element::setOffset(const math::point2f_t &pnt) {
  offset_.original = pnt;
  offset_.markAsDirty();

  // for (auto &node : getChildNodes()) {
  //   auto child = NodeUtil::cast<Element>(node);
  //   child->setOffset(pnt);
  // }
}

void Element::setOffset(f32_t x, f32_t y) { setOffset(math::point2f_t(x, y)); }

auto Element::getOffset() -> ElementOffset & { return offset_; }

void Element::updateOffset() {
  if (!offset_.dirty) {
    return;
  }

  if (position_ == ElementPosition::RELATIVE) {
    auto parentOpt = this->getParentNode();
    if (!parentOpt.has_value()) {
      offset_.computed = offset_.original;
    } else {
      auto parent = core::NodeUtil::cast<Element>(parentOpt);
      auto parentAreaHolder = parent->getAreaHolder();
      auto parentAreaPosition = parentAreaHolder.getPosition<ui::AreaType::IDX_CNT>();
      auto parentContentSize = parentAreaHolder.getContentSize();

      auto x = 0.0F, y = 0.0F;
      auto alignmentBase = core::toBase<math::Alignment>(alignment_);
      auto childContentSize = this->getAreaHolder().getContentSize();

      if (alignmentBase & math::ConvFromXAlign<math::HorzAlign::CENTER>()) {
        x = (parentContentSize.getW() - childContentSize.getW()) / 2;
      } else if (alignmentBase & math::ConvFromXAlign<math::HorzAlign::RIGHT>()) {
        x = (parentContentSize.getW() - childContentSize.getW());
      }

      if (alignmentBase & math::ConvFromXAlign<math::VertAlign::CENTER>()) {
        y = (parentContentSize.getH() - childContentSize.getH()) / 2;
      } else if (alignmentBase & math::ConvFromXAlign<math::VertAlign::BOTTOM>()) {
        y = (parentContentSize.getH() - childContentSize.getH());
      }

      offset_.computed = math::point2f_t(offset_.computed.getX() + x, offset_.computed.getY() + y);
    }
  } else if (position_ == ElementPosition::ABSOLUTE || position_ == ElementPosition::FIXED) {
    //     // auto parentInnerSize = parent->getInnerSize();
    offset_.computed = offset_.original;
  } else {
    offset_.computed = offset_.original;
  }

  offset_.dirty = false;
}

auto Element::getAreaHolder() const -> AreaHolder { return holder_; }

auto Element::getInnerSize() const -> math::size2f_t { return holder_.getSize<AreaType::IDX_PAD>(); }

auto Element::getOuterSize() const -> math::size2f_t { return holder_.getSize<AreaType::IDX_BRD>(); }

auto Element::getOuterSizeWithMargin() const -> math::size2f_t { return holder_.getSize<AreaType::IDX_MRG>(); }

auto Element::handleAddNode(const core::EventTypedefs::UniquePtr_t &evt) -> bool {
  auto *nodeEventData = static_cast<core::NodeEventData *>(evt->getData());

  /** При добавлении нового узла обновляем смещение всех дочерних элементов по отношению к родителю. */
  recursiveUpdateItemOffset(math::point2f_zero);

  // auto prevElement = (ElementTypedefs::SharedPtr_t) nullptr;

  // auto prevNodeIndex = NodeChainExtension::getPrevItem(nodeEventData->nodeidx);
  // if (!prevNodeIndex.has_value()) {
  //   std::clog << "[UI Element::handleAddNode]: prevNodeIndex has no value" << std::endl;
  // } else {
  //   prevElement = NodeExtension::getChild<Element>(this, prevNodeIndex);
  // }

  // recursiveUpdate(prevElement, currElement);
  return true;
}

}  // namespace sway::ui
