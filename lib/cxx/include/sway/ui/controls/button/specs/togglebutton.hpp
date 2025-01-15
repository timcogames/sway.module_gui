#ifndef SWAY_UI_TOGGLEBUTTON_HPP
#define SWAY_UI_TOGGLEBUTTON_HPP

#include <sway/ui/_stdafx.hpp>
#include <sway/ui/controls/button/button.hpp>
#include <sway/ui/painter.hpp>

namespace sway::ui {

class ToggleButton : public Button {
public:
#pragma region "Define aliases"
  /** \~english @name Define aliases */ /** \~russian @name Определение алиасов */
  /** @{ */

  using SharedPtr_t = ToggleButtonSharedPtr_t;

  /** @} */
#pragma endregion

#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  ToggleButton(BuilderPtr_t builder, const std::string &text);

  virtual ~ToggleButton() = default;

  /** @} */
#pragma endregion

#pragma region "Overridden Button methods"

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void repaint(PainterSharedPtr_t painter));

#pragma endregion

  [[nodiscard]] auto isChecked() const -> bool { return checked_; }

  void setChecked(bool val) { checked_ = val; }

protected:
  bool checked_;
};

}  // namespace sway::ui

#endif  // SWAY_UI_TOGGLEBUTTON_HPP
