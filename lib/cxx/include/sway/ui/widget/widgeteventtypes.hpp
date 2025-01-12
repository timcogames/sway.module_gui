#ifndef SWAY_UI_WIDGET_WIDGETEVENTTYPES_HPP
#define SWAY_UI_WIDGET_WIDGETEVENTTYPES_HPP

#include <sway/core.hpp>

namespace sway::ui {

enum class WidgetEventType : u32_t { MOUSE_OVER = 50, MOUSE_OUT, POINTER_ENTER, POINTER_LEAVE };

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGET_WIDGETEVENTTYPES_HPP
