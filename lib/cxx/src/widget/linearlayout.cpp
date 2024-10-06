#include <sway/ui/builder.hpp>
#include <sway/ui/widget/linearlayout.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)
NS_BEGIN(widget)

LinearLayout::LinearLayout(BuilderPtr_t builder, Orientation orien)
    : Layout(builder, orien) {}

void LinearLayout::build() {
  auto offset = math::point2f_zero;

  for (auto node : this->getChildNodes()) {
    auto child = std::static_pointer_cast<Widget>(node);

    const auto size = child->getSize();
    const auto boundingSize = math::size2f_t(size.getW(), size.getH());

    if (this->getOrientation() == Orientation::HORZ) {
      offset.setX(offset.getX() + boundingSize.getW());
    } else if (this->getOrientation() == Orientation::VERT) {
      offset.setY(offset.getY() + boundingSize.getH());
    }

    child->setOffset(offset);
  }
}

NS_END()  // namespace widget
NS_END()  // namespace ui
NS_END()  // namespace sway
