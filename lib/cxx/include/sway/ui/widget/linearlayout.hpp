#ifndef SWAY_UI_WIDGET_LINEARLAYOUT_HPP
#define SWAY_UI_WIDGET_LINEARLAYOUT_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/layout.hpp>
#include <sway/ui/widget/layoutorientations.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class LinearLayout : public Layout {
public:
  LinearLayout(Builder *builder, LayoutOrientation orien);

  virtual ~LinearLayout() = default;

  void build();
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_LINEARLAYOUT_HPP
