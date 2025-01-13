#include <sway/ui/builder.hpp>
#include <sway/ui/controls/button/specs/togglebutton.hpp>

namespace sway::ui {

ToggleButton::ToggleButton(BuilderPtr_t builder, const std::string &text)
    : Button(builder, text)
    , checked_(false) {}

void ToggleButton::update() { Button::update(); }

void ToggleButton::repaint(PainterSharedPtr_t painter) { Button::repaint(painter); }

}  // namespace sway::ui
