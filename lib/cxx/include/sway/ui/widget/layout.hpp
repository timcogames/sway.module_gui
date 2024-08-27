#ifndef SWAY_UI_WIDGET_LAYOUT_HPP
#define SWAY_UI_WIDGET_LAYOUT_HPP

#include <sway/core.hpp>
#include <sway/ui/orientable.hpp>
#include <sway/ui/orientations.hpp>
#include <sway/ui/widget/widget.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class Layout : public Widget, public Orientable {
public:
#pragma region "Ctors/Dtor"

  Layout(BuilderPtr_t builder, Orientation orien);

  virtual ~Layout() = default;

#pragma endregion
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_LAYOUT_HPP
