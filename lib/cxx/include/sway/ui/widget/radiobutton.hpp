#ifndef SWAY_UI_WIDGET_RADIOBUTTON_HPP
#define SWAY_UI_WIDGET_RADIOBUTTON_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/togglebutton.hpp>

#include <memory>
#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class RadioButton : public ToggleButton {
public:
  using Ptr_t = RadioButton *;
  using SharedPtr_t = std::shared_ptr<RadioButton>;

#pragma region "Ctors/Dtor"

  RadioButton(BuilderPtr_t builder, const std::string &text);

  virtual ~RadioButton() = default;

#pragma endregion

#pragma region "Override ToggleButton methods"

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void repaint(Painter::SharedPtr_t painter));

#pragma endregion
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_RADIOBUTTON_HPP
