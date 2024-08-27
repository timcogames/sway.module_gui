#ifndef SWAY_UI_WIDGET_TOGGLEBUTTON_HPP
#define SWAY_UI_WIDGET_TOGGLEBUTTON_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/button.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class ToggleButton : public Button {
public:
#pragma region "Ctors/Dtor"

  ToggleButton(BuilderPtr_t builder, const std::string &text);

  virtual ~ToggleButton() = default;

#pragma endregion

#pragma region "Override Button methods"

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void repaint(Painter::SharedPtr_t painter));

#pragma endregion

  [[nodiscard]]
  auto isChecked() const -> bool {
    return checked_;
  }

  void setChecked(bool val) { checked_ = val; }

protected:
  bool checked_;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_TOGGLEBUTTON_HPP
