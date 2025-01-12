#ifndef SWAY_UI_RADIOBUTTON_HPP
#define SWAY_UI_RADIOBUTTON_HPP

#include <sway/core.hpp>
#include <sway/ui/controls/button/specs/togglebutton.hpp>
#include <sway/ui/painter.hpp>

#include <string>

namespace sway::ui {

class RadioButton : public ToggleButton {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  RadioButton(BuilderTypedefs::Ptr_t builder, const std::string &text);

  virtual ~RadioButton() = default;

  /** @} */
#pragma endregion

#pragma region "Overridden ToggleButton methods"

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void repaint(PainterTypedefs::SharedPtr_t painter));

#pragma endregion
};

}  // namespace sway::ui

#endif  // SWAY_UI_RADIOBUTTON_HPP
