#include <sway/core/container/nodeutil.hpp>
#include <sway/ui/layout/layoutitem.hpp>

namespace sway::ui {

LayoutItem::LayoutItem()
    : mouseFilter_(ois::MouseFilter::STOP) {}

void LayoutItem::recursiveUpdateItemOffset(const math::point2f_t parentOffset) {
  auto elementOffset = math::point2f_t(
      parentOffset.getX() + getOffset().original.getX(), parentOffset.getY() + getOffset().original.getY());

  for (auto i = 0; i < getNumOfChildNodes(); ++i) {
    auto node = getChildAt(i);
    if (!node.has_value()) {
      continue;
    }

    auto element = core::NodeUtil::cast<Element>(node.value());
    element->getOffset().computed = math::point2f_t(
        elementOffset.getX() /* + item->getMargin().getX() */, elementOffset.getY() /* + item->getMargin().getY() */);
    element->recursiveUpdateItemOffset(parentOffset);
  }
}

}  // namespace sway::ui
