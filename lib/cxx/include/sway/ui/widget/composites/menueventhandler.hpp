#ifndef SWAY_UI_WIDGET_MENUEVENTHANDLER_HPP
#define SWAY_UI_WIDGET_MENUEVENTHANDLER_HPP

#include <sway/ui/_stdafx.hpp>
#include <sway/ui/orientations.hpp>
#include <sway/ui/widget/composites/_typedefs.hpp>
#include <sway/ui/widget/composites/menucontrolscheme.hpp>

namespace sway::ui {

struct MenuEventHandler : public core::EventHandler {
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  MenuEventHandler(MenuPtr_t menu);

  virtual ~MenuEventHandler() override = default;

  /** @} */
#pragma endregion

  virtual auto invoke(core::EventTypedefs::UniquePtr_t &&evt) -> bool;

  void onKeyEvent(ois::typedefs::KeyEventPtr_t evt);

private:
  MenuPtr_t menu_;
  MenuControlScheme scheme_;
};

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGET_MENUEVENTHANDLER_HPP
