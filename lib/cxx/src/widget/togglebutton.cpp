#include <sway/ui/builder.hpp>
#include <sway/ui/widget/togglebutton.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)
NS_BEGIN(widget)

ToggleButton::ToggleButton(BuilderTypedefs::Ptr_t builder, const std::string &text)
    : Button(builder, text)
    , checked_(false) {}

void ToggleButton::update() { Button::update(); }

void ToggleButton::repaint(PainterTypedefs::SharedPtr_t painter) { Button::repaint(painter); }

NS_END()  // namespace widget
NS_END()  // namespace ui
NS_END()  // namespace sway
