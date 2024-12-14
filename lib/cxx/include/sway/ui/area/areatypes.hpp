#ifndef SWAY_UI_AREATYPES_HPP
#define SWAY_UI_AREATYPES_HPP

#include <sway/core.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

enum class AreaType : i32_t { NONE = GLOB_IDX_INVALID, IDX_MRG = GLOB_IDX_INITIAL, IDX_BRD, IDX_PAD, IDX_CNT, Latest };

constexpr sway::u32_t NUM_AREA_TYPES = core::detail::toBase(AreaType::Latest);
constexpr sway::u32_t NUM_AREA_TYPES_WITHOUT_CNT = NUM_AREA_TYPES - 1;

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_AREATYPES_HPP
