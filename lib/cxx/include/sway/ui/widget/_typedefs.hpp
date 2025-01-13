#ifndef SWAY_UI_WIDGETS_TYPEDEFS_HPP
#define SWAY_UI_WIDGETS_TYPEDEFS_HPP

#include <sway/ui/_stdafx.hpp>

namespace sway::ui {

class Widget;

using WidgetPtr_t = Widget *;
using WidgetSharedPtr_t = std::shared_ptr<Widget>;

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGETS_TYPEDEFS_HPP
