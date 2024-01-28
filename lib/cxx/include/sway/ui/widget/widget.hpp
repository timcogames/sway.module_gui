#ifndef SWAY_UI_WIDGET_WIDGET_HPP
#define SWAY_UI_WIDGET_WIDGET_HPP

#include <sway/core.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class Widget : public core::container::Node {
public:
  Widget();

  ~Widget();
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_WIDGET_HPP
