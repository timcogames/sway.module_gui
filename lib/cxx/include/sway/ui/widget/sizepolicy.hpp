#ifndef SWAY_UI_WIDGETS_SIZEPOLICY_HPP
#define SWAY_UI_WIDGETS_SIZEPOLICY_HPP

#include <sway/ui/_stdafx.hpp>
#include <sway/ui/widget/_typedefs.hpp>
#include <sway/ui/widget/sizepolicytypes.hpp>

namespace sway::ui {

struct SizePolicy {
  math::size2f_t min;  //!< \~english Minimum size. \~russian Минимальный размер.
  math::size2f_t max;  //!< \~english Maximum size. \~russian Максимальный размер.
  SizePolicyType horiType;  //!< \~english Horizontal policy type. \~russian Тип политики размера по горизонтали.
  SizePolicyType vertType;  //!< \~english Vertical policy type. \~russian Тип политики размера по вертикали.

  SizePolicy()
      : min(math::size2f_zero)
      , max(math::size2f_zero)
      , horiType(SizePolicyType::PREFERRED)
      , vertType(SizePolicyType::PREFERRED) {}
};

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGETS_SIZEPOLICY_HPP
