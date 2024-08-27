#include <sway/ui/builder.hpp>
#include <sway/ui/widget/linearlayout.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

LinearLayout::LinearLayout(BuilderPtr_t builder, Orientation orien)
    : Layout(builder, orien) {}

void LinearLayout::build() {
  auto offset = math::point2f_zero;

  for (auto node : this->getChildNodes()) {
    auto child = std::static_pointer_cast<Widget>(node);

    const auto size = child->getSize();
    const auto boundingSize = math::size2f_t(size.getW(), size.getH());

    child->setOffset(offset);

    if (this->getOrientation() == Orientation::HORZ) {
      offset.setX(offset.getX() + boundingSize.getW());
    } else if (this->getOrientation() == Orientation::VERT) {
      offset.setY(offset.getY() + boundingSize.getH());
    }
  }
}

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
