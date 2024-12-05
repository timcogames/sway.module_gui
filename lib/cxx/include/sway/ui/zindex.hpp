#ifndef SWAY_UI_ZINDEX_HPP
#define SWAY_UI_ZINDEX_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

enum class ZIndex : u32_t { NONE = 0, BACKDROP = 10, DIALOG = 20, DLG_HEAD = 21, Latest };

inline auto getZIndex(i32_t val) -> f32_t { return math::util::clamp<f32_t>((f32_t)val / 1000.0F, 0.0F, 1.0F); }

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_ZINDEX_HPP