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
  if (!offset_.dirty) {
    return;
  }

  // auto prevElemOffset = prev ? prev->getOffset().computed : math::point2f_zero;

  if (position_ == ElementPosition::RELATIVE) {
    auto parentOpt = this->getParentNode();
    if (!parentOpt.has_value()) {
      // TODO
    } else {
      auto parent = cast<Element>(parentOpt);
      auto parentOffset = parent->getOffset().computed;
      auto parentAreaHolder = parent->getAreaHolder();
      auto parentAreaPosition = parentAreaHolder.getPosition<ui::AreaType::IDX_CNT>();
      auto parentContentSize = parentAreaHolder.getContentSize();

      // offset_.computed =
      //     math::point2f_t(prevElemOffset.getX() + parentOffset.getX(), prevElemOffset.getY() + parentOffset.getY());
      offset_.computed = math::point2f_t(parentOffset.getX(), parentOffset.getY());

      auto x = 0.0F, y = 0.0F;
      auto alignmentBase = core::detail::toBase<math::Alignment>(alignment_);
      auto childContentSize = getAreaHolder().getContentSize();

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
    // auto parentInnerSize = parent->getInnerSize();
    offset_.computed = offset_.original;
  } else {
    offset_.computed = offset_.original;
  }

  offset_.dirty = false;
}

void Element::recursiveUpdate(Element::SharedPtr_t lhs, Element::SharedPtr_t rhs) {
  rhs->updateOffset(lhs);

  for (auto i = 0; i < rhs->getChildNodes().size(); i++) {
    auto prev = (Element::SharedPtr_t) nullptr;
    auto prevOpt = rhs->getChildAt(i - 1);
    if (!prevOpt.has_value()) {
      // TODO
    } else {
      prev = cast<Element>(prevOpt);
    }

    Element::SharedPtr_t curr = nullptr;
    auto currOpt = rhs->getChildAt(i);
    if (!currOpt.has_value()) {
      // TODO
    } else {
      curr = cast<Element>(currOpt);
    }

    recursiveUpdate(prev, curr);
  }
}

auto Element::getAreaHolder() const -> ElementAreaHolder { return holder_; }

auto Element::getInnerSize() const -> math::size2f_t { return holder_.getSize<AreaType::IDX_PAD>(); }

auto Element::getOuterSize() const -> math::size2f_t { return holder_.getSize<AreaType::IDX_BRD>(); }

auto Element::getOuterSizeWithMargin() const -> math::size2f_t { return holder_.getSize<AreaType::IDX_MRG>(); }

/**
 * \~russian @brief Возвращает последний сегмент в индексе целевого узла.
 *
 * @param[in] target Целевой индекс узла.
 * @return core::container::NodeIdx::ChainItemIndex_t
 */
auto getLastNodeIndexSegment(const core::container::NodeIdx &target) -> core::container::NodeIdx::ChainItemIndex_t {
  return target.getIdxAt(target.getDepth() - 1);
}

/**
 * \~russian @brief Возвращает индекс предыдущего узла в цепочке.
 *
 * @param[in] target Целевой индекс узла.
 * @return std::optional<core::container::NodeIdx>
 */
auto getPrevChainItem(const core::container::NodeIdx &target) -> std::optional<core::container::NodeIdx> {
  if (auto lastSegment = getLastNodeIndexSegment(target); lastSegment > GLOB_NULL) {
    auto prev = core::container::NodeIdx();
    prev.setChain(target.getParent(), lastSegment - 1);
    return prev;
  }

  return std::nullopt;
}

void Element::handleAddNode(core::foundation::Event::Ptr_t evt) {
  auto *nodeEventData = static_cast<core::container::NodeEventData *>(evt->data());

  auto currElement = getChild<Element>(nodeEventData->nodeidx);
  auto prevElement = (ElementTypedefs::SharedPtr_t) nullptr;

  auto prevNodeIndex = getPrevChainItem(nodeEventData->nodeidx);
  if (!prevNodeIndex.has_value()) {
    // TODO
  } else {
    prevElement = getChild<Element>(prevNodeIndex.value());
  }

  recursiveUpdate(prevElement, currElement);
}

NS_END()  // namespace ui
NS_END()  // namespace sway
