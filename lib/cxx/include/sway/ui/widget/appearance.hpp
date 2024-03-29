#ifndef SWAY_UI_WIDGET_APPEARANCE_HPP
#define SWAY_UI_WIDGET_APPEARANCE_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>

#include <array>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

enum class WidgetColorGroup : u32_t { INACTIVE, ACTIVE, DISABLED };
enum class WidgetColorState : u32_t { NORM, HOVERED, FOCUSED };

using col4f_stats_t = std::array<math::col4f_t, 3>;
using col4f_group_t = std::array<col4f_stats_t, 3>;

struct Appearance {
  col4f_group_t text;
  col4f_group_t background;
  col4f_group_t border;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_APPEARANCE_HPP
