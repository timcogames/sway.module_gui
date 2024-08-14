#ifndef SWAY_UI_WIDGET_ITEM_HPP
#define SWAY_UI_WIDGET_ITEM_HPP

#include <sway/core.hpp>
#include <sway/ui/widget/widget.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

class Builder;

NAMESPACE_BEGIN(widget)

class Item : public Widget {
public:
  Item(Builder *builder)
      : Widget(builder) {}

  virtual ~Item() = default;

  void select() {}

  void deselect() {}

  void toggle() {}
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_ITEM_HPP
