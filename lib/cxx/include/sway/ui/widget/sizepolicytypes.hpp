#ifndef SWAY_UI_WIDGETS_SIZEPOLICYTYPES_HPP
#define SWAY_UI_WIDGETS_SIZEPOLICYTYPES_HPP

#include <sway/ui/_stdafx.hpp>
#include <sway/ui/widget/typedefs.hpp>

namespace sway::ui {

/**
 * @enum SizePolicyType
 * @brief \~english Enumeration of internal widget size policy types. \~russian Перечисление внутренних типов политик
 * размера виджета.
 */
enum class SizePolicyType : u32_t {
  NONE = GLOB_NULL,  //!< \~english Ignored policy. \~russian Игнорируется политика.
  FIXED_MIN,  //!< \~english Fixed minimum. \~russian Фиксированный минимум.
  FIXED_MAX,  //!< \~english Fixed maximum. \~russian Фиксированный максимум.
  PREFERRED,  //!< \~english Preferred size. \~russian Предпочтительный размер.
  EXPANDING  //!< \~english Expanding size. \~russian Растягивающийся размер.
};

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGETS_SIZEPOLICYTYPES_HPP
