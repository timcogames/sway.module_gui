#ifndef SWAY_UI_CURSOR_HPP
#define SWAY_UI_CURSOR_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

struct Cursor {
  math::point2f_t pnt;
  bool visible;
};

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_CURSOR_HPP
