#ifndef SWAY_UI_WIDGET_RADIOBUTTON_HPP
#define SWAY_UI_WIDGET_RADIOBUTTON_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/togglebutton.hpp>

#include <memory>
#include <string>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class RadioButton : public ToggleButton {
public:
  using Ptr_t = RadioButton *;
  using SharedPtr_t = std::shared_ptr<RadioButton>;

#pragma region "Ctors/Dtor"

  RadioButton(BuilderTypedefs::Ptr_t builder, const std::string &text);

  DTOR_VIRTUAL_DEFAULT(RadioButton);

#pragma endregion

#pragma region "Overridden ToggleButton methods"

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void repaint(PainterTypedefs::SharedPtr_t painter));

#pragma endregion
};

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGET_RADIOBUTTON_HPP
