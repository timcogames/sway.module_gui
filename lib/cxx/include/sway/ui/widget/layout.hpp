#ifndef SWAY_UI_WIDGET_LAYOUT_HPP
#define SWAY_UI_WIDGET_LAYOUT_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/linearlayoutorientations.hpp>
#include <sway/ui/widget/widget.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class Layout : public Widget {
public:
  Layout(Builder *builder);

  virtual ~Layout() = default;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_LAYOUT_HPP
