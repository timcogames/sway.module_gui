#include <sway/ui/builder.hpp>
#include <sway/ui/widget/layout.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

Layout::Layout(Builder *builder)
    : Widget(builder) {
  setMouseFilter(ois::MouseFilter::PASS);
}

LinearLayout::LinearLayout(Builder *builder, LinearLayoutOrientation orientation)
    : Layout(builder)
    , orientation_(orientation) {}

void LinearLayout::build() {
  math::vec2f_t offset(0.0F, 0.0F);

  for (auto node : this->getChildNodes()) {
    auto child = std::static_pointer_cast<Widget>(node);

    const auto size = child->getSize();
    const auto margin = child->getMargin();
    const auto boundingSize =
        math::size2f_t(margin.getL() + size.getW() + margin.getR(), margin.getT() + size.getH() + margin.getB());

    child->setPosition(offset);

    if (orientation_ == LinearLayoutOrientation::HORZ) {
      offset.setX(offset.getX() + boundingSize.getW());
    } else if (orientation_ == LinearLayoutOrientation::VERT) {
      offset.setY(offset.getY() + boundingSize.getH());
    }
  }
}

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
