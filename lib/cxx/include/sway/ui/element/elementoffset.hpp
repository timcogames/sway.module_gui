#ifndef SWAY_UI_ELEMENTOFFSET_HPP
#define SWAY_UI_ELEMENTOFFSET_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>

namespace sway::ui {

struct ElementOffset {
  math::point2f_t original; /*< \~english Original position. \~russian Оригинальное положение. */
  math::point2f_t computed; /*< \~english Calculated position. \~russian Расчитанное положение. */
  bool dirty; /*< \~english Dirty flag. \~russian Необходимость пересчета. */

  ElementOffset()
      : original(math::point2f_zero)
      , computed(math::point2f_zero)
      , dirty(false) {}

  void markAsDirty() { dirty = true; }
};

}  // namespace sway::ui

#endif  // SWAY_UI_ELEMENTOFFSET_HPP
