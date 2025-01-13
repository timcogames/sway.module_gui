#include <sway/core.hpp>
#include <sway/ui/builder.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/droptarget.hpp>

namespace sway::ui {

DropTarget::DropTarget(BuilderPtr_t builder)
    : Widget(builder) {}

void DropTarget::update() {}

void DropTarget::repaint(PainterSharedPtr_t painter) {}

}  // namespace sway::ui
