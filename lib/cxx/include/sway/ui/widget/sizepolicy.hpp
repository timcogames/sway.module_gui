#ifndef SWAY_UI_WIDGETS_SIZEPOLICY_HPP
#define SWAY_UI_WIDGETS_SIZEPOLICY_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ui/widget/sizepolicytypes.hpp>
#include <sway/ui/widget/typedefs.hpp>

namespace sway::ui {

struct SizePolicy {
  math::size2f_t min; /*< Минимальный размер. */
  math::size2f_t max; /*< Максимальный размер. */
  SizePolicyType horiType; /*< Тип политики размера по горизонтали. */
  SizePolicyType vertType; /*< Тип политики размера по вертикали. */

  SizePolicy()
      : min(math::size2f_zero)
      , max(math::size2f_zero)
      , horiType(SizePolicyType::PREFERRED)
      , vertType(SizePolicyType::PREFERRED) {}
};

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGETS_SIZEPOLICY_HPP
