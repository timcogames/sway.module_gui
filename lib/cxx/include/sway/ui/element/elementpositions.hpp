#ifndef SWAY_UI_ELEMENTPOSITIONS_HPP
#define SWAY_UI_ELEMENTPOSITIONS_HPP

#include <sway/core.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

enum class ElementPosition : i32_t { RELATIVE, ABSOLUTE, FIXED, Latest };

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_ELEMENTPOSITIONS_HPP
