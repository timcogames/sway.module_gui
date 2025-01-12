#ifndef SWAY_UI_WIDGET_MENU_HPP
#define SWAY_UI_WIDGET_MENU_HPP

#include <sway/core.hpp>
#include <sway/ui/layout/specs/linearlayout.hpp>
#include <sway/ui/orientations.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/menueventhandler.hpp>
#include <sway/ui/widget/composites/menuitem.hpp>
#include <sway/ui/widget/typedefs.hpp>

#include <memory>
#include <string>
#include <unordered_map>

namespace sway::ui {

class Menu : public Widget {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  Menu(BuilderTypedefs::Ptr_t builder, Orientation orien);

  virtual ~Menu();

  /** @} */
#pragma endregion

#pragma region "Overridden Widget methods"

  // MTHD_OVERRIDE(void update());

  // MTHD_OVERRIDE(void repaint(PainterTypedefs::SharedPtr_t painter));

#pragma endregion

  void addItem(const std::string &text);

private:
  core::Subscribable::Subscriber_t subscriber_;
  int selectedItem_;
};

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGET_MENU_HPP
