#ifndef SWAY_UI_WIDGET_TYPES_HPP
#define SWAY_UI_WIDGET_TYPES_HPP

#include <sway/core.hpp>
#include <sway/ui/widget/areatypes.hpp>

#include <array>
#include <memory>

#define NUM_OF_AREAS (sway::core::detail::toBase(sway::ui::AreaType::Latest))

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

#pragma region "Area"

class Element;

using ElementPtr_t = Element *;

#pragma endregion

#pragma region "Area"

class Area;
class BoxArea;
class ContentArea;

using AreaPtr_t = Area *;
using AreaSharedPtr_t = std::shared_ptr<Area>;

using BoxAreaPtr_t = BoxArea *;
using BoxAreaSharedPtr_t = std::shared_ptr<BoxArea>;

using ContentAreaPtr_t = ContentArea *;
using ContentAreaSharedPtr_t = std::shared_ptr<ContentArea>;

using AreaHolder_t = std::array<AreaSharedPtr_t, NUM_OF_AREAS>;

template <AreaType TYPE>
using OutputAreaType_t = typename std::conditional<TYPE == AreaType::IDX_CNT, ContentArea, BoxArea>::type;
;
#pragma endregion

NAMESPACE_BEGIN(widget)

#pragma region "Widget"

class Widget;

using WidgetPtr_t = Widget *;
using WidgetSharedPtr_t = std::shared_ptr<Widget>;

#pragma endregion

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_TYPES_HPP
