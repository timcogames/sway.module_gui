#ifndef SWAY_UI_LAYOUT_TYPEDEFS_HPP
#define SWAY_UI_LAYOUT_TYPEDEFS_HPP

#include <sway/ui/_stdafx.hpp>

namespace sway::ui {

class LinearLayout;

using LinearLayoutPtr_t = LinearLayout *;
using LinearLayoutSharedPtr_t = std::shared_ptr<LinearLayout>;

}  // namespace sway::ui

#endif  // SWAY_UI_LAYOUT_TYPEDEFS_HPP
