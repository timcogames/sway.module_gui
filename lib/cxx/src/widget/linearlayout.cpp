#include <sway/ui/builder.hpp>
#include <sway/ui/widget/linearlayout.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

LinearLayout::LinearLayout(Builder::Ptr_t builder, LayoutOrientation orien)
    : Layout(builder, orien) {}

void LinearLayout::build() {
  math::vec2f_t offset(0.0F, 0.0F);

  for (auto node : this->getChildNodes()) {
    auto child = std::static_pointer_cast<Widget>(node);

    const auto size = child->getSize();
    const auto margin = child->getMargin();
    const auto boundingSize = math::size2f_t(margin->getLR() + size.getW(), margin->getTB() + size.getH());

    child->setPosition(offset);

    if (this->getOrientation() == LayoutOrientation::HORZ) {
      offset.setX(offset.getX() + boundingSize.getW());
    } else if (this->getOrientation() == LayoutOrientation::VERT) {
      offset.setY(offset.getY() + boundingSize.getH());
    }
  }
}

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
