#include <sway/core.hpp>
#include <sway/ui/builder.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/overlay.hpp>

#include <memory>
#include <string>
#include <unordered_map>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

Overlay::Overlay(BuilderPtr_t builder)
    : Widget(builder) {}

Overlay::~Overlay() {}

void Overlay::update() {}

void Overlay::repaint(Painter::SharedPtr_t painter) {
  auto offset = this->getOffset(ElementPosition::RELATIVE);
  painter->drawRect(math::rect4f_t(offset.getX(), offset.getY(), this->getSize()), this->getBackgroundColor());

  Widget::repaint(painter);
}

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
