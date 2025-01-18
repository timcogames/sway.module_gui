#ifndef SWAY_UI_TRANSFORM_DIMENSIONTYPES_HPP
#define SWAY_UI_TRANSFORM_DIMENSIONTYPES_HPP

#include <sway/ui/_stdafx.hpp>

namespace sway::ui {

/**
 * @ingroup transform
 * @{
 */

enum class DimensionType : u32_t {
  NONE = GLOB_IDX_INITIAL,
  WDT,  //!< \~english Width dimension. \~russian Ширина.
  HGT,  //!< \~english Height dimension. \~russian Высота.
  ALL,  //!< \~english Mask to cover all flags. \~russian Маска, покрывающая все флаги.
  Latest
};

/** @} */

}  // namespace sway::ui

#endif  // SWAY_UI_TRANSFORM_DIMENSIONTYPES_HPP
