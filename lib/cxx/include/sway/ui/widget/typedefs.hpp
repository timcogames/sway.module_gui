#ifndef SWAY_UI_WIDGET_TYPEDEFS_HPP
#define SWAY_UI_WIDGET_TYPEDEFS_HPP

#include <sway/core.hpp>
#include <sway/ui/widget/areatypes.hpp>

#include <array>
#include <type_traits>  // std::conditional

NS_BEGIN_SWAY()
NS_BEGIN(ui)

DECLARE_PTR_TYPES(Area)
DECLARE_PTR_TYPES(BoxArea)
DECLARE_PTR_TYPES(ContentArea)
DECLARE_PTR_TYPES(Element)
DECLARE_PTR_TYPES(ElementAreaHolder)

using AreaHolder_t = std::array<AreaSharedPtr_t, NUM_OF_AREAS>;

template <AreaType TYPE>
using OutputAreaType_t = typename std::conditional<TYPE == AreaType::IDX_CNT, ContentArea, BoxArea>::type;

NS_BEGIN(widget)
DECLARE_PTR_TYPES(Widget)
DECLARE_PTR_TYPES(Label)
DECLARE_PTR_TYPES(Button)
DECLARE_PTR_TYPES(Popup)
DECLARE_PTR_TYPES(Dialog)
DECLARE_PTR_TYPES(Draggable)
DECLARE_PTR_TYPES(Backdrop)
DECLARE_PTR_TYPES(DropTarget)
DECLARE_PTR_TYPES(Menu)
DECLARE_PTR_TYPES(MenuItem)
NS_END()  // namespace widget

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGET_TYPEDEFS_HPP
