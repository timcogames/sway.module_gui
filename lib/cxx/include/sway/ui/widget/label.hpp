#ifndef SWAY_UI_WIDGET_LABEL_HPP
#define SWAY_UI_WIDGET_LABEL_HPP

#include <sway/core.hpp>
#include <sway/ui/widget/widget.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class Label : public Widget {
public:
  Label();

  ~Label();
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_LABEL_HPP
