#include <sway/ui/builder.hpp>
#include <sway/ui/widget/radiobutton.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

RadioButton::RadioButton(BuilderPtr_t builder, const std::string &text)
    : ToggleButton(builder, text) {}

void RadioButton::update() { ToggleButton::update(); }

void RadioButton::repaint(Painter::SharedPtr_t painter) { ToggleButton::repaint(painter); }

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
