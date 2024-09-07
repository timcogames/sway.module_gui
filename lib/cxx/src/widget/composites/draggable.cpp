#include <sway/core.hpp>
#include <sway/ui/builder.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/draggable.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

Draggable::Draggable(BuilderPtr_t builder)
    : Widget(builder)
    , hovering_(false) {
  subscribe(this, "MouseClicked", EVENT_HANDLER(Draggable, handleMouseClickedEvent));
}

Draggable::~Draggable() {}

void Draggable::handleMouseClickedEvent(core::foundation::Event *evt) { std::cout << "clicked" << std::endl; }

void Draggable::update() {
  const auto oldState = hovering_;
  hovering_ = this->builder_->getWidgetUnderPointer()->getNodeIdx().equal(this->getNodeIdx());
  if (oldState == hovering_) {
    return;
  }
}

void Draggable::repaint(Painter::SharedPtr_t painter) {
  auto offset = this->getOffset();
  painter->drawRect(math::rect4f_t(offset.getX(), offset.getY(), this->getSize()), this->getBackgroundColor(), 0.01F);

  Widget::repaint(painter);
}

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
