#include <sway/ui/layout/layoutitem.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

LayoutItem::LayoutItem()
    : mouseFilter_(ois::MouseFilter::Enum::STOP) {}

void LayoutItem::recursiveUpdateItemOffset(const math::point2f_t parentOffset) {
  auto elementOffset = math::point2f_t(
      parentOffset.getX() + getOffset().original.getX(), parentOffset.getY() + getOffset().original.getY());

  for (auto i = 0; i < getNumOfChildNodes(); ++i) {
    auto node = getChildAt(i);
    if (!node.has_value()) {
      continue;
    }

    auto element = NodeUtil::cast<Element>(node.value());
    element->getOffset().computed = math::point2f_t(
        elementOffset.getX() /* + item->getMargin().getX() */, elementOffset.getY() /* + item->getMargin().getY() */);
    element->recursiveUpdateItemOffset(parentOffset);
  }
}

NS_END()  // namespace ui
NS_END()  // namespace sway
