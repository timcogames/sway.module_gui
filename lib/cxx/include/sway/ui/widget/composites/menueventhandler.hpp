#ifndef SWAY_UI_WIDGET_MENUEVENTHANDLER_HPP
#define SWAY_UI_WIDGET_MENUEVENTHANDLER_HPP

#include <sway/core.hpp>
#include <sway/ois.hpp>
#include <sway/ui/orientations.hpp>
#include <sway/ui/widget/composites/menucontrolscheme.hpp>

#include <memory>

namespace sway::ui {

class Menu;

struct MenuEventHandler : public core::EventHandler {
  MenuEventHandler(Menu *menu);

  virtual ~MenuEventHandler() override = default;

  virtual auto invoke(core::EventTypedefs::UniquePtr_t &&evt) -> bool;

  void onKeyEvent(ois::typedefs::KeyEventPtr_t evt);

private:
  Menu *menu_;
  MenuControlScheme scheme_;
};

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGET_MENUEVENTHANDLER_HPP
