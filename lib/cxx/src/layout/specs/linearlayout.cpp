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

NS_END()  // namespace ui
NS_END()  // namespace sway
