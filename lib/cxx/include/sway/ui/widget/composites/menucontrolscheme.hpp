#ifndef SWAY_UI_WIDGET_MENUCONTROLSCHEME_HPP
#define SWAY_UI_WIDGET_MENUCONTROLSCHEME_HPP

#include <sway/core.hpp>
#include <sway/ois.hpp>
#include <sway/ui/orientations.hpp>

#include <memory>

namespace sway::ui {

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

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGET_MENUCONTROLSCHEME_HPP
