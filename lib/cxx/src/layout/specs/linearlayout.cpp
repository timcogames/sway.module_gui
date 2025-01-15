#include <sway/ui/builder.hpp>
#include <sway/ui/layout/specs/linearlayout.hpp>

namespace sway::ui {

auto LinearLayout::create(BuilderPtr_t builder, Orientation orien) -> LinearLayoutSharedPtr_t {
  return std::make_shared<LinearLayout>(builder, orien);
}

LinearLayout::LinearLayout(BuilderPtr_t builder, Orientation orien)
    : Layout(builder, orien) {}

void LinearLayout::setAdjacentChildOffsets() {
  auto accum = math::point2f_zero;

  for (auto i = 0; i < getNumOfChildNodes(); ++i) {
    auto node = getChildAt(i);
    if (!node.has_value()) {
      continue;
    }

    auto item = core::NodeUtil::cast<LayoutItem>(node.value());
    item->setOffset(accum);

    if (getOrientation() == Orientation::HORZ) {
      accum.setX(accum.getX() + Layout::getCellSize(this).getW());
    } else if (getOrientation() == Orientation::VERT) {
      accum.setY(accum.getY() + Layout::getCellSize(this).getH());
    }
  }
}

}  // namespace sway::ui
