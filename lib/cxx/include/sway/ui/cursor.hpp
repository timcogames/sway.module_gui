#ifndef SWAY_UI_CURSOR_HPP
#define SWAY_UI_CURSOR_HPP

#include <sway/ui/_stdafx.hpp>

namespace sway::ui {

struct Cursor {
  math::point2f_t pnt;
  bool visible;
};

}  // namespace sway::ui

#endif  // SWAY_UI_CURSOR_HPP
