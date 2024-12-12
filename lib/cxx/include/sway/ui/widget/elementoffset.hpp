#ifndef SWAY_UI_WIDGETS_ELEMENTOFFSET_HPP
#define SWAY_UI_WIDGETS_ELEMENTOFFSET_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ui/widget/typedefs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

struct ElementOffset {
  math::point2f_t original;  ///< Оригинальное положение.
  math::point2f_t computed;  ///< Расчитанное положение.
  bool dirty;  ///< Необходимость пересчета.

  ElementOffset()
      : original(math::point2f_zero)
      , computed(math::point2f_zero)
      , dirty(false) {}

  void markAsDirty() { dirty = true; }
};

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGETS_ELEMENTOFFSET_HPP
