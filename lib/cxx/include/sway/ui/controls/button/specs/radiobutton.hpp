#ifndef SWAY_UI_RADIOBUTTON_HPP
#define SWAY_UI_RADIOBUTTON_HPP

#include <sway/ui/_stdafx.hpp>
#include <sway/ui/controls/button/specs/togglebutton.hpp>
#include <sway/ui/painter.hpp>

namespace sway::ui {

class RadioButton : public ToggleButton {
public:
#pragma region "Pointer aliases"
  /** \~english @name Pointer aliases */ /** \~russian @name Типы указателей */

  using SharedPtr_t = RadioButtonSharedPtr_t;

  /** @{ */
#pragma endregion

#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  RadioButton(BuilderPtr_t builder, const std::string &text);

  virtual ~RadioButton() = default;

  /** @} */
#pragma endregion

#pragma region "Overridden ToggleButton methods"

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void repaint(PainterSharedPtr_t painter));

#pragma endregion
};

}  // namespace sway::ui

#endif  // SWAY_UI_RADIOBUTTON_HPP
