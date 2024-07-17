#ifndef SWAY_UI_WIDGET_RADIOBUTTON_HPP
#define SWAY_UI_WIDGET_RADIOBUTTON_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/togglebutton.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class RadioButton : public ToggleButton {
public:
  RadioButton(Builder::Ptr_t builder, const std::string &text);

  virtual ~RadioButton() = default;

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void paintEvent(Painter::SharedPtr_t painter));
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_RADIOBUTTON_HPP
