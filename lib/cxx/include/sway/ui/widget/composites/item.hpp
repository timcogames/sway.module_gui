#ifndef SWAY_UI_WIDGET_ITEM_HPP
#define SWAY_UI_WIDGET_ITEM_HPP

#include <sway/core.hpp>
#include <sway/ui/widget/widget.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class Builder;

NS_BEGIN(widget)

class Item : public Widget {
public:
  Item(BuilderTypedefs::Ptr_t builder)
      : Widget(builder) {}

  DTOR_VIRTUAL_DEFAULT(Item);

  void select() {}

  void deselect() {}

  void toggle() {}
};

NS_END()  // namespace widget
NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGET_ITEM_HPP
