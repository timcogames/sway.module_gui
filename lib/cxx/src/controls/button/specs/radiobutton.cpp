#include <sway/ui/builder.hpp>
#include <sway/ui/controls/button/specs/radiobutton.hpp>

namespace sway::ui {

RadioButton::RadioButton(BuilderTypedefs::Ptr_t builder, const std::string &text)
    : ToggleButton(builder, text) {}

void RadioButton::update() { ToggleButton::update(); }

void RadioButton::repaint(PainterTypedefs::SharedPtr_t painter) { ToggleButton::repaint(painter); }

}  // namespace sway::ui
