#ifndef SWAY_UI_WIDGETS_TYPEDEFS_HPP
#define SWAY_UI_WIDGETS_TYPEDEFS_HPP

#include <sway/core.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class Element;
namespace ElementTypedefs {
using Ptr_t = Element *;
using SharedPtr_t = std::shared_ptr<Element>;
}  // namespace ElementTypedefs

class Widget;
namespace WidgetTypedefs {
using SharedPtr_t = std::shared_ptr<Widget>;
}  // namespace WidgetTypedefs

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGETS_TYPEDEFS_HPP
