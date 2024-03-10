#include <sway/ui/widget/widget.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

Widget::Widget()
    : rect_(math::rect4f_t(0.0F, 0.0F, 1.0F, 1.0F)) {}

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
