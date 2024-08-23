#ifndef SWAY_UI_WIDGET_LAYOUT_HPP
#define SWAY_UI_WIDGET_LAYOUT_HPP

#include <sway/core.hpp>
#include <sway/ui/widget/layoutorientations.hpp>
#include <sway/ui/widget/widget.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class Layout : public Widget {
public:
#pragma region "Ctors/Dtor"

  Layout(BuilderPtr_t builder, LayoutOrientation orien);

  virtual ~Layout() = default;

#pragma endregion

  auto getOrientation() const -> LayoutOrientation { return orientation_; }

private:
  LayoutOrientation orientation_;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_LAYOUT_HPP
