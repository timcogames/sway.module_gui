#ifndef SWAY_UI_WIDGETS_SIZEPOLICY_HPP
#define SWAY_UI_WIDGETS_SIZEPOLICY_HPP

#include <sway/ui/_stdafx.hpp>
#include <sway/ui/transform/dimension.hpp>
#include <sway/ui/transform/dimensiontypes.hpp>
#include <sway/ui/transform/sizepolicytypes.hpp>
#include <sway/ui/widget/_typedefs.hpp>

namespace sway::ui {

/**
 * @ingroup transform
 * @{
 */

using DimensionSize_t = std::array<Dimension, 2>;

struct SizePolicy {
  DimensionSize_t dimensions = {{{{0.0f, 0.0f, 0.0f}, DimensionUnit::PX, SizePolicyType::WRAP_CONTENT},
      {{0.0f, 0.0f, 0.0f}, DimensionUnit::PX, SizePolicyType::WRAP_CONTENT}}};

  void setResizePolicy(DimensionType dim, SizePolicyType policy) {
    if (dim == DimensionType::WDT || dim == DimensionType::ALL) {
      dimensions[math::Size<f32_t>::IDX_WDT].policy = policy;
    }

    if (dim == DimensionType::HGT || dim == DimensionType::ALL) {
      dimensions[math::Size<f32_t>::IDX_HGT].policy = policy;
    }
  }
};

/** @} */

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGETS_SIZEPOLICY_HPP
