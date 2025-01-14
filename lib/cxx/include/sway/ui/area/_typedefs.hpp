#ifndef SWAY_UI_AREA_TYPEDEFS_HPP
#define SWAY_UI_AREA_TYPEDEFS_HPP

#include <sway/ui/_stdafx.hpp>
#include <sway/ui/area/areatypes.hpp>

namespace sway::ui {

class Area;

using AreaSharedPtr_t = std::shared_ptr<Area>;
using AreaOptionalSharedPtr_t = std::optional<AreaSharedPtr_t>;
using AreaContainer_t = std::array<AreaSharedPtr_t, NUM_AREA_TYPES>;

class ContentArea;

using ContentAreaSharedPtr_t = std::shared_ptr<ContentArea>;

class BoxArea;
using BoxAreaSharedPtr_t = std::shared_ptr<BoxArea>;

template <AreaType TYPE>
using OutputAreaType_t = typename std::conditional<TYPE == AreaType::IDX_CNT, ContentArea, BoxArea>::type;

}  // namespace sway::ui

#endif  // SWAY_UI_AREA_TYPEDEFS_HPP
