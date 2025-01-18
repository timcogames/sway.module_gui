#ifndef SWAY_UI_TRANSFORM_DIMENSION_HPP
#define SWAY_UI_TRANSFORM_DIMENSION_HPP

#include <sway/ui/_stdafx.hpp>
#include <sway/ui/transform/dimensionunits.hpp>
#include <sway/ui/transform/sizepolicytypes.hpp>

namespace sway::ui {

/**
 * @ingroup transform
 * @{
 */

struct Dimension {
  std::tuple<f32_t /** base */, f32_t /** min */, f32_t /** max */> value;
  DimensionUnit unit = DimensionUnit::PX;
  SizePolicyType policy;
};

/** @} */

}  // namespace sway::ui

#endif  // SWAY_UI_TRANSFORM_DIMENSION_HPP
