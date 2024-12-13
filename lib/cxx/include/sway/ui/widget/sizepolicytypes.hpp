#ifndef SWAY_UI_WIDGETS_SIZEPOLICYTYPES_HPP
#define SWAY_UI_WIDGETS_SIZEPOLICYTYPES_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ui/widget/typedefs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

/**
 * @enum SizePolicyType
 * \~russian @brief Перечисление внутренних типов политик размера виджета.
 */
enum class SizePolicyType : u32_t {
  NONE = GLOB_NULL, /*< Игнорируется политика. */
  FIXED_MIN, /*< Фиксированный минимум. */
  FIXED_MAX, /*< Фиксированный максимум. */
  PREFERRED, /*< Предпочтительный размер. */
  EXPANDING /*< Растягивающийся размер. */
};

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGETS_SIZEPOLICYTYPES_HPP
