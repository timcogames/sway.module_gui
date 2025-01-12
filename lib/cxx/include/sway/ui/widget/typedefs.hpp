#ifndef SWAY_UI_WIDGET_TYPEDEFS_HPP
#define SWAY_UI_WIDGET_TYPEDEFS_HPP

#include <sway/core.hpp>

namespace sway::ui {

class Widget;
class Popup;
class Dialog;
class Draggable;
class Backdrop;
class DropTarget;
class Menu;
class MenuItem;

using BackdropSharedPtr_t = std::shared_ptr<Backdrop>;
using DraggableSharedPtr_t = std::shared_ptr<Draggable>;

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGET_TYPEDEFS_HPP
