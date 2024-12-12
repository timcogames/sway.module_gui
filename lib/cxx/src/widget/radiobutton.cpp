#include <sway/ui/builder.hpp>
#include <sway/ui/widget/radiobutton.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)
NS_BEGIN(widget)

RadioButton::RadioButton(BuilderTypedefs::Ptr_t builder, const std::string &text)
    : ToggleButton(builder, text) {}

void RadioButton::update() { ToggleButton::update(); }

void RadioButton::repaint(PainterTypedefs::SharedPtr_t painter) { ToggleButton::repaint(painter); }

NS_END()  // namespace widget
NS_END()  // namespace ui
NS_END()  // namespace sway
