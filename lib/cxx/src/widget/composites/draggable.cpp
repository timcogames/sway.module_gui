#include <sway/core.hpp>
#include <sway/ui/builder.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/draggable.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

Draggable::Draggable(BuilderPtr_t builder)
    : Widget(builder)
    , hovering_(false) {}

Draggable::~Draggable() {}

void Draggable::update() {
  const auto oldState = hovering_;
  hovering_ = this->builder_->getWidgetUnderPointer()->getNodeIdx().equal(this->getNodeIdx());
  if (oldState == hovering_) {
    return;
  }
}

void Draggable::repaint(Painter::SharedPtr_t painter) {}

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
