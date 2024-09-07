#ifndef SWAY_UI_WIDGET_TYPES_HPP
#define SWAY_UI_WIDGET_TYPES_HPP

#include <sway/core.hpp>
#include <sway/ui/widget/areatypes.hpp>

#include <array>
#include <type_traits>  // std::conditional

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

DECLARE_CLASS_POINTER_TYPES(Area)
DECLARE_CLASS_POINTER_TYPES(BoxArea)
DECLARE_CLASS_POINTER_TYPES(ContentArea)
DECLARE_CLASS_POINTER_TYPES(Element)
DECLARE_CLASS_POINTER_TYPES(ElementAreaHolder)

using AreaHolder_t = std::array<AreaSharedPtr_t, NUM_OF_AREAS>;

template <AreaType TYPE>
using OutputAreaType_t = typename std::conditional<TYPE == AreaType::IDX_CNT, ContentArea, BoxArea>::type;

NAMESPACE_BEGIN(widget)
DECLARE_CLASS_POINTER_TYPES(Widget)
DECLARE_CLASS_POINTER_TYPES(Label)
NAMESPACE_END(widget)

NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_TYPES_HPP
