#ifndef SWAY_UI_WIDGET_LAYOUT_HPP
#define SWAY_UI_WIDGET_LAYOUT_HPP

#include <sway/core.hpp>
#include <sway/ui/orientable.hpp>
#include <sway/ui/orientations.hpp>
#include <sway/ui/widget/widget.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)
NS_BEGIN(widget)

class Layout : public Widget, public Orientable {
public:
#pragma region "Ctors/Dtor"

  Layout(BuilderPtr_t builder, Orientation orien);

  virtual ~Layout() = default;

#pragma endregion
};

NS_END()  // namespace widget
NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGET_LAYOUT_HPP
