#ifndef SWAY_UI_WIDGET_TYPES_HPP
#define SWAY_UI_WIDGET_TYPES_HPP

#include <sway/core.hpp>

#include <memory>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class Widget;

using WidgetPtr_t = Widget *;
using WidgetSharedPtr_t = std::shared_ptr<Widget>;

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_TYPES_HPP
