#ifndef SWAY_UI_WIDGET_TOGGLEBUTTON_HPP
#define SWAY_UI_WIDGET_TOGGLEBUTTON_HPP

#include <sway/core.hpp>
#include <sway/ui/controls/button/button.hpp>
#include <sway/ui/painter.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class ToggleButton : public Button {
public:
#pragma region "Ctors/Dtor"

  ToggleButton(BuilderTypedefs::Ptr_t builder, const std::string &text);

  DTOR_VIRTUAL_DEFAULT(ToggleButton);

#pragma endregion

#pragma region "Overridden Button methods"

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void repaint(PainterTypedefs::SharedPtr_t painter));

#pragma endregion

  [[nodiscard]]
  auto isChecked() const -> bool {
    return checked_;
  }

  void setChecked(bool val) { checked_ = val; }

protected:
  bool checked_;
};

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGET_TOGGLEBUTTON_HPP
