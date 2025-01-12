#ifndef SWAY_UI_WIDGETS_TYPEDEFS_HPP
#define SWAY_UI_WIDGETS_TYPEDEFS_HPP

#include <sway/core.hpp>

namespace sway::ui {

class Widget;
namespace WidgetTypedefs {
using Ptr_t = Widget *;
using SharedPtr_t = std::shared_ptr<Widget>;
}  // namespace WidgetTypedefs

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGETS_TYPEDEFS_HPP
