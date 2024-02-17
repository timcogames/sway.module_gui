#include <sway/ui/widget/widget.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

Widget::Widget() {
  // Empty
}

void Widget::update() {
  for (auto const &child : this->getChildNodes()) {
    std::static_pointer_cast<Widget>(child)->update();
  }
}

void Widget::draw(std::shared_ptr<Painter> painter) {
  for (auto const &child : this->getChildNodes()) {
    std::static_pointer_cast<Widget>(child)->draw(painter);
  }
}

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
