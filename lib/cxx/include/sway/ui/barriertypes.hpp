#ifndef SWAY_UI_BARRIERTYPES_HPP
#define SWAY_UI_BARRIERTYPES_HPP

#include <sway/core.hpp>

namespace sway::ui {

enum class BarrierType : u32_t { NONE = 0, PSEUDO, LAYOUT, Latest };

}  // namespace sway::ui

#endif  // SWAY_UI_BARRIERTYPES_HPP
