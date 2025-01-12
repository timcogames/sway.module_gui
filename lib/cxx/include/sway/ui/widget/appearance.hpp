#ifndef SWAY_UI_WIDGET_APPEARANCE_HPP
#define SWAY_UI_WIDGET_APPEARANCE_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>

#include <array>

namespace sway::ui {

enum class WidgetColorState : u32_t { NONE = 0, NORM, HOVERED, FOCUSED, Latest };
enum class WidgetColorGroup : u32_t { NONE = 0, INACTIVE, ACTIVE, DISABLED, Latest };

struct Appearance {
  using Stats_t = std::array<math::col4f_t, core::toBase(WidgetColorState::Latest)>;
  using Group_t = std::array<Stats_t, core::toBase(WidgetColorGroup::Latest)>;

  Group_t text;
  Group_t background;
  Group_t border;
};

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGET_APPEARANCE_HPP
