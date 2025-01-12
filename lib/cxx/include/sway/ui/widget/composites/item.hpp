#ifndef SWAY_UI_WIDGET_ITEM_HPP
#define SWAY_UI_WIDGET_ITEM_HPP

#include <sway/core.hpp>
#include <sway/ui/_typedefs.hpp>
#include <sway/ui/widget/widget.hpp>

namespace sway::ui {

class Item : public Widget {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  Item(BuilderTypedefs::Ptr_t builder)
      : Widget(builder) {}

  virtual ~Item() = default;

  /** @} */
#pragma endregion

  void select() {}

  void deselect() {}

  void toggle() {}
};

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGET_ITEM_HPP
