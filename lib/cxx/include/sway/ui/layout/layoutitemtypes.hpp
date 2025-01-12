#ifndef SWAY_UI_LAYOUTITEMTYPES_HPP
#define SWAY_UI_LAYOUTITEMTYPES_HPP

#include <sway/core.hpp>

namespace sway::ui {

enum class LayoutItemTypes : u32_t { NONE = 0, WIDGET, CONTAINER, Latest };

}  // namespace sway::ui

#endif  // SWAY_UI_LAYOUTITEMTYPES_HPP
