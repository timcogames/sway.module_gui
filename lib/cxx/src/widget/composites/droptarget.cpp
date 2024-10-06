#include <sway/core.hpp>
#include <sway/ui/builder.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/droptarget.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)
NS_BEGIN(widget)

DropTarget::DropTarget(BuilderPtr_t builder)
    : Widget(builder) {}

void DropTarget::update() {}

void DropTarget::repaint(Painter::SharedPtr_t painter) {}

NS_END()  // namespace widget
NS_END()  // namespace ui
NS_END()  // namespace sway
