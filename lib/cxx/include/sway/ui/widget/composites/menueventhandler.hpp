#ifndef SWAY_UI_WIDGET_MENUEVENTHANDLER_HPP
#define SWAY_UI_WIDGET_MENUEVENTHANDLER_HPP

#include <sway/core.hpp>
#include <sway/ois.hpp>
#include <sway/ui/orientations.hpp>
#include <sway/ui/widget/composites/menucontrolscheme.hpp>

#include <memory>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class Menu;

struct MenuEventHandler : public core::evts::EventHandler {
  MenuEventHandler(Menu *menu);

  virtual ~MenuEventHandler() override = default;

  MTHD_OVERRIDE(auto invoke(const core::foundation::Event::UniquePtr_t &evt) -> bool) final;

  void onKeyEvent(ois::KeyEvent::Ptr_t evt);

private:
  Menu *menu_;
  MenuControlScheme scheme_;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_MENUEVENTHANDLER_HPP
