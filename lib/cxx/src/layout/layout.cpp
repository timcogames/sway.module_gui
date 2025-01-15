#include <sway/ui/builder.hpp>
#include <sway/ui/layout/specs/linearlayout.hpp>

namespace sway::ui {

auto Layout::getCellSize(ElementPtr_t elem) -> math::size2f_t {
  return elem->getAreaHolder().getContentSize() / elem->getNumOfChildNodes();
}

Layout::Layout(BuilderPtr_t builder, Orientation orien)
    : LayoutItem()
    , Orientable(orien) {
  setMouseFilter(ois::MouseFilter::PASS);
  subscribe(this, "NodeAdded", EVENT_HANDLER(Layout, handleItemAdded));
}

auto Layout::handleItemAdded(const core::EventTypedefs::UniquePtr_t &evt) -> bool {
  auto *nodeEventData = static_cast<core::NodeEventData *>(evt->getData());

  std::cout << Representation<core::NodeIndex>::get(this->getNodeIndex()) << std::endl;

  /** При добавлении нового узла обновляем смещение всех дочерних элементов по отношению к родителю. */
  recursiveUpdateItemOffset(math::point2f_zero);

  // auto prevElement = (ElementSharedPtr_t) nullptr;

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
