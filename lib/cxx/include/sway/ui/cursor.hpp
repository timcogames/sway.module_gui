#ifndef SWAY_UI_CURSOR_HPP
#define SWAY_UI_CURSOR_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

struct Cursor {
  math::point2f_t pnt;
  bool visible;
};

NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_CURSOR_HPP
