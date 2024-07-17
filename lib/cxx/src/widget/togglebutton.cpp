#include <sway/ui/builder.hpp>
#include <sway/ui/widget/togglebutton.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

ToggleButton::ToggleButton(Builder::Ptr_t builder, const std::string &text)
    : Button(builder, text)
    , checked_(false) {}

void ToggleButton::update() { Button::update(); }

void ToggleButton::paintEvent(Painter::SharedPtr_t painter) { Button::paintEvent(painter); }

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
