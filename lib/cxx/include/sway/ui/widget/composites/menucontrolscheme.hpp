#ifndef SWAY_UI_WIDGET_MENUCONTROLSCHEME_HPP
#define SWAY_UI_WIDGET_MENUCONTROLSCHEME_HPP

#include <sway/core.hpp>
#include <sway/ois.hpp>
#include <sway/ui/orientations.hpp>

#include <memory>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

struct MenuControlScheme {
  ois::ControlButtonDefinition prevItem;
  ois::ControlButtonDefinition nextItem;
  ois::ControlButtonDefinition enter;

  static auto reset(Orientation orien) -> MenuControlScheme {
    MenuControlScheme scheme;

    scheme.prevItem.button = ois::ControlButtonUtil::makeKeyboardControlButton(
        orien == Orientation::HORZ ? ois::KeyCode::KC_LEFT : ois::KeyCode::KC_UP);
    scheme.prevItem.description = "Prev MenuItem";

    scheme.nextItem.button = ois::ControlButtonUtil::makeKeyboardControlButton(
        orien == Orientation::HORZ ? ois::KeyCode::KC_RIGHT : ois::KeyCode::KC_DOWN);
    scheme.nextItem.description = "Next MenuItem";

    scheme.enter.button = ois::ControlButtonUtil::makeKeyboardControlButton(ois::KeyCode::KC_ENTER);
    scheme.enter.description = "Enter";

    return scheme;
  }
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_MENUCONTROLSCHEME_HPP
