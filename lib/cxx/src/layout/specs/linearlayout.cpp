#include <sway/ui/builder.hpp>
#include <sway/ui/layout/specs/linearlayout.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

auto LinearLayout::create(BuilderTypedefs::Ptr_t builder, Orientation orien) -> LinearLayoutTypedefs::SharedPtr_t {
  return std::make_shared<LinearLayout>(builder, orien);
}

LinearLayout::LinearLayout(BuilderTypedefs::Ptr_t builder, Orientation orien)
    : Layout(builder, orien) {}

void LinearLayout::build() {
  auto accum = math::point2f_zero;
  auto contentSize = getAreaHolder().getContentSize();

  for (auto &node : getChildNodes()) {
    auto child = NodeUtil::cast<Widget>(node);
    child->setOffset(accum);

    if (getOrientation() == Orientation::HORZ) {
      accum.setX(accum.getX() + Layout::getCellSize(this).getW());
    } else if (getOrientation() == Orientation::VERT) {
      accum.setY(accum.getY() + Layout::getCellSize(this).getH());
    }
  }
}

void LinearLayout::recursiveUpdateItemOffset(const math::point2f_t parentOffset) {
  auto accum = math::point2f_zero;

  for (auto i = 0; i < getNumOfChildNodes(); ++i) {
    auto node = getChildAt(i);
    if (!node.has_value()) {
      continue;
    }

    auto element = NodeUtil::cast<Element>(node.value());
    element->setOffset(accum);

    if (getOrientation() == Orientation::HORZ) {
      accum.setX(accum.getX() + Layout::getCellSize(this).getW());
    } else if (getOrientation() == Orientation::VERT) {
      accum.setY(accum.getY() + Layout::getCellSize(this).getH());
    }
  }

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
