#ifndef SWAY_UI_WIDGET_ITEM_HPP
#define SWAY_UI_WIDGET_ITEM_HPP

#include <sway/core.hpp>
#include <sway/ui/_typedefs.hpp>
#include <sway/ui/widget/widget.hpp>

namespace sway::ui {

class Item : public Widget {
public:
  Item(BuilderTypedefs::Ptr_t builder)
      : Widget(builder) {}

  DTOR_VIRTUAL_DEFAULT(Item);

  void select() {}

  void deselect() {}

  void toggle() {}
};

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGET_ITEM_HPP
