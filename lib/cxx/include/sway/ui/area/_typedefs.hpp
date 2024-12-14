#ifndef SWAY_UI_AREA_TYPEDEFS_HPP
#define SWAY_UI_AREA_TYPEDEFS_HPP

#include <sway/core.hpp>
#include <sway/ui/area/areatypes.hpp>

#include <array>
#include <type_traits>  // std::conditional

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class Area;
namespace AreaTypedefs {
using SharedPtr_t = std::shared_ptr<Area>;
using OptionalSharedPtr_t = std::optional<SharedPtr_t>;
using Container_t = std::array<SharedPtr_t, NUM_AREA_TYPES>;
}  // namespace AreaTypedefs

class ContentArea;
namespace ContentAreaTypedefs {
using SharedPtr_t = std::shared_ptr<ContentArea>;
}  // namespace ContentAreaTypedefs

class BoxArea;
namespace BoxAreaTypedefs {
using SharedPtr_t = std::shared_ptr<BoxArea>;
}  // namespace BoxAreaTypedefs

template <AreaType TYPE>
using OutputAreaType_t = typename std::conditional<TYPE == AreaType::IDX_CNT, ContentArea, BoxArea>::type;

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_AREA_TYPEDEFS_HPP
