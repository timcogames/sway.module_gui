#ifndef SWAY_UI_WIDGETS_SIZEPOLICYTYPES_HPP
#define SWAY_UI_WIDGETS_SIZEPOLICYTYPES_HPP

#include <sway/ui/_stdafx.hpp>
#include <sway/ui/widget/_typedefs.hpp>

namespace sway::ui {

/**
 * @ingroup transform
 * @{
 */

/**
 * @enum SizePolicyType
 * @brief \~english Enumeration of internal widget size policy types. \~russian Перечисление внутренних типов политик
 * размера виджета.
 */
enum class SizePolicyType : u32_t { FIXED = 0, WRAP_CONTENT, MATCH_PARENT };

/** @} */

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGETS_SIZEPOLICYTYPES_HPP
