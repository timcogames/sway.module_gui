#ifndef SWAY_UI_WIDGET_WIDGETEVENTTYPES_HPP
#define SWAY_UI_WIDGET_WIDGETEVENTTYPES_HPP

#include <sway/core.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)
NS_BEGIN(widget)

enum class WidgetEventType : u32_t { MOUSE_OVER = 50, MOUSE_OUT, POINTER_ENTER, POINTER_LEAVE };

NS_END()  // namespace widget
NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGET_WIDGETEVENTTYPES_HPP
