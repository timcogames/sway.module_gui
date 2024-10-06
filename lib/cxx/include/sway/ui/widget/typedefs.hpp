#ifndef SWAY_UI_WIDGET_TYPEDEFS_HPP
#define SWAY_UI_WIDGET_TYPEDEFS_HPP

#include <sway/core.hpp>
#include <sway/ui/widget/areatypes.hpp>

#include <array>
#include <type_traits>  // std::conditional

NS_BEGIN_SWAY()
NS_BEGIN(ui)

DECLARE_CLASS_POINTER_TYPES(Area)
DECLARE_CLASS_POINTER_TYPES(BoxArea)
DECLARE_CLASS_POINTER_TYPES(ContentArea)
DECLARE_CLASS_POINTER_TYPES(Element)
DECLARE_CLASS_POINTER_TYPES(ElementAreaHolder)

using AreaHolder_t = std::array<AreaSharedPtr_t, NUM_OF_AREAS>;

template <AreaType TYPE>
using OutputAreaType_t = typename std::conditional<TYPE == AreaType::IDX_CNT, ContentArea, BoxArea>::type;

NS_BEGIN(widget)
DECLARE_CLASS_POINTER_TYPES(Widget)
DECLARE_CLASS_POINTER_TYPES(Label)
DECLARE_CLASS_POINTER_TYPES(Button)
DECLARE_CLASS_POINTER_TYPES(Popup)
DECLARE_CLASS_POINTER_TYPES(Dialog)
DECLARE_CLASS_POINTER_TYPES(Draggable)
DECLARE_CLASS_POINTER_TYPES(Backdrop)
DECLARE_CLASS_POINTER_TYPES(DropTarget)
DECLARE_CLASS_POINTER_TYPES(Menu)
DECLARE_CLASS_POINTER_TYPES(MenuItem)
NS_END()  // namespace widget

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGET_TYPEDEFS_HPP
