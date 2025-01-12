#include <sway/ui/builder.hpp>
#include <sway/ui/controls/button/specs/togglebutton.hpp>

namespace sway::ui {

ToggleButton::ToggleButton(BuilderTypedefs::Ptr_t builder, const std::string &text)
    : Button(builder, text)
    , checked_(false) {}

void ToggleButton::update() { Button::update(); }

void ToggleButton::repaint(PainterTypedefs::SharedPtr_t painter) { Button::repaint(painter); }

}  // namespace sway::ui
