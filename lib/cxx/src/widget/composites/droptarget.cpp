#include <sway/core.hpp>
#include <sway/ui/builder.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/droptarget.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

DropTarget::DropTarget(BuilderPtr_t builder)
    : Widget(builder) {}

void DropTarget::update() {}

void DropTarget::repaint(Painter::SharedPtr_t painter) {}

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
