#include <sway/ui/widget/element.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

Element::Element()
    : position_(ElementPosition::RELATIVE)
    , alignment_(math::Alignment::LEFT_TOP) {
  this->subscribe(this, "NodeAdded", EVENT_HANDLER(Element, handleAddNode));
}

void Element::setPosition(ElementPosition pos) { position_ = pos; }

auto Element::getPosition() const -> ElementPosition { return position_; }

void Element::setOffset(const math::point2f_t &pnt) {
  offset_.original = pnt;
  offset_.markAsDirty();
  // recursiveUpdate(this->getSharedFrom<Element>(this));
}

void Element::setOffset(f32_t x, f32_t y) { setOffset(math::point2f_t(x, y)); }

auto Element::getOffset() -> ElementOffset & { return offset_; }

void Element::updateOffset(Element::SharedPtr_t prev) {
  auto prevElemOffset = math::point2f_zero;
  if (prev != nullptr) {
    prevElemOffset = prev->getOffset().computed;
  }

  if (offset_.dirty) {
    if (position_ == ElementPosition::RELATIVE) {
      auto parentOpt = this->getParentNode();
      if (!parentOpt.has_value()) {
        // TODO
      } else {
        auto parent = std::static_pointer_cast<Element>(parentOpt.value());
        auto parentOffset = parent->getOffset().computed;
        auto parentAreaPosition = parent->getAreaHolder().getPosition<ui::AreaType::IDX_CNT>();
        auto parentAreaSize = parent->getAreaHolder().getContentSize();

        offset_.computed =
            math::point2f_t(prevElemOffset.getX() + parentOffset.getX(), prevElemOffset.getY() + parentOffset.getY());

        auto x = 0.0F;
        auto y = 0.0F;
        auto sz = getAreaHolder().getContentSize();

        if (core::detail::toBase<math::Alignment>(alignment_) & math::ConvFromXAlign<math::HorzAlign::CENTER>()) {
          x = (parentAreaSize.getW() - sz.getW()) / 2;
        } else if (core::detail::toBase<math::Alignment>(alignment_) & math::ConvFromXAlign<math::HorzAlign::RIGHT>()) {
          x = (parentAreaSize.getW() - sz.getW());
        }

        if (core::detail::toBase<math::Alignment>(alignment_) & math::ConvFromXAlign<math::VertAlign::CENTER>()) {
          y = (parentAreaSize.getH() - sz.getH()) / 2;
        } else if (core::detail::toBase<math::Alignment>(alignment_) &
                   math::ConvFromXAlign<math::VertAlign::BOTTOM>()) {
          y = (parentAreaSize.getH() - sz.getH());
        }

        offset_.computed = math::point2f_t(offset_.computed.getX() + x, offset_.computed.getY() + y);
      }
    } else if (position_ == ElementPosition::ABSOLUTE || position_ == ElementPosition::FIXED) {
      // auto parentInnerSize = parent->getInnerSize();
      offset_.computed = offset_.original;
    } else {
      offset_.computed = offset_.original;
    }

    offset_.dirty = false;
  }
}

void Element::recursiveUpdate(Element::SharedPtr_t lhs, Element::SharedPtr_t rhs) {
  std::static_pointer_cast<Element>(rhs)->updateOffset(lhs);

  for (auto i = 0; i < rhs->getChildNodes().size(); i++) {
    Element::SharedPtr_t prev = nullptr;
    auto prevOpt = rhs->getChildAt(i - 1);
    if (!prevOpt.has_value()) {
      // TODO
    } else {
      prev = std::static_pointer_cast<Element>(prevOpt.value());
    }

    Element::SharedPtr_t curr = nullptr;
    auto currOpt = rhs->getChildAt(i);
    if (!currOpt.has_value()) {
      // TODO
    } else {
      curr = std::static_pointer_cast<Element>(currOpt.value());
    }

    recursiveUpdate(prev, curr);
  }
}

auto Element::getAreaHolder() const -> ElementAreaHolder { return holder_; }

auto Element::getInnerSize() const -> math::size2f_t { return holder_.getSize<AreaType::IDX_PAD>(); }

auto Element::getOuterSize() const -> math::size2f_t { return holder_.getSize<AreaType::IDX_BRD>(); }

auto Element::getOuterSizeWithMargin() const -> math::size2f_t { return holder_.getSize<AreaType::IDX_MRG>(); }

void Element::handleAddNode(core::foundation::Event::Ptr_t evt) {
  auto evtdata = static_cast<core::container::NodeEventData *>(evt->data());

  auto currNodeIdx = evtdata->nodeidx;
  auto currIdx = currNodeIdx.getIdxAt(currNodeIdx.getDepth() - 1);
  auto currElem = std::static_pointer_cast<Element>(this->getChildNode(currNodeIdx));

  core::container::NodeIdx::ChainVec_t prevNodeChain = currNodeIdx.getChain();
  prevNodeChain.pop_back();
  auto prevElemNodeIdx = core::container::NodeIdx();
  prevElemNodeIdx.setChain(prevNodeChain, currIdx - 1);
  auto prevElem = std::static_pointer_cast<Element>(this->getChildNode(prevElemNodeIdx));

  recursiveUpdate(prevElem, currElem);
}

NS_END()  // namespace ui
NS_END()  // namespace sway
