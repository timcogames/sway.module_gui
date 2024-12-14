#ifndef SWAY_UI_LAYOUT_TYPEDEFS_HPP
#define SWAY_UI_LAYOUT_TYPEDEFS_HPP

#include <sway/core.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class LinearLayout;
namespace LinearLayoutTypedefs {
using Ptr_t = LinearLayout *;
using SharedPtr_t = std::shared_ptr<LinearLayout>;
}  // namespace LinearLayoutTypedefs

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_LAYOUT_TYPEDEFS_HPP
