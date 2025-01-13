#ifndef SWAY_UI_LAYOUT_TYPEDEFS_HPP
#define SWAY_UI_LAYOUT_TYPEDEFS_HPP

#include <sway/ui/_stdafx.hpp>

namespace sway::ui {

class LinearLayout;
namespace LinearLayoutTypedefs {
using Ptr_t = LinearLayout *;
using SharedPtr_t = std::shared_ptr<LinearLayout>;
}  // namespace LinearLayoutTypedefs

}  // namespace sway::ui

#endif  // SWAY_UI_LAYOUT_TYPEDEFS_HPP
