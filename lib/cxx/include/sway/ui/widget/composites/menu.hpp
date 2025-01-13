#ifndef SWAY_UI_WIDGET_MENU_HPP
#define SWAY_UI_WIDGET_MENU_HPP

#include <sway/ui/_stdafx.hpp>
#include <sway/ui/layout/specs/linearlayout.hpp>
#include <sway/ui/orientations.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/menueventhandler.hpp>
#include <sway/ui/widget/composites/menuitem.hpp>
#include <sway/ui/widget/typedefs.hpp>

namespace sway::ui {

class Menu : public Widget {
public:
#pragma region "Pointer aliases"
  /** \~english @name Pointer aliases */ /** \~russian @name Типы указателей */

  using Ptr_t = MenuPtr_t;
  using SharedPtr_t = MenuSharedPtr_t;

  /** @{ */
#pragma endregion

#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  Menu(BuilderPtr_t builder, Orientation orien);

  virtual ~Menu();

  /** @} */
#pragma endregion

#pragma region "Overridden Widget methods"

  // MTHD_OVERRIDE(void update());

  // MTHD_OVERRIDE(void repaint(PainterSharedPtr_t painter));

#pragma endregion

  void addItem(const std::string &text);

private:
  core::Subscribable::Subscriber_t subscriber_;
  int selectedItem_;
};

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGET_MENU_HPP
