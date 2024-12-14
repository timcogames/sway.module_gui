#ifndef SWAY_UI_TEXTVIEW_TYPEDEFS_HPP
#define SWAY_UI_TEXTVIEW_TYPEDEFS_HPP

#include <sway/core.hpp>

#include <array>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class TextView;
namespace TextViewTypedefs {
using SharedPtr_t = std::shared_ptr<TextView>;
}  // namespace TextViewTypedefs

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_TEXTVIEW_TYPEDEFS_HPP
