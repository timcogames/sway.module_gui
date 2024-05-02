#include <sway/ui/builder.hpp>
#include <sway/ui/widget/radiobutton.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

RadioButton::RadioButton(Builder *builder, const std::string &text)
    : ToggleButton(builder, text)
    , checked_(false) {}

void RadioButton::update() { ToggleButton::update(); }

void RadioButton::paintEvent(std::shared_ptr<Painter> painter) { ToggleButton::paintEvent(painter); }

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
