#ifndef SWAY_UI_WIDGET_MENUITEM_HPP
#define SWAY_UI_WIDGET_MENUITEM_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ui/_typedefs.hpp>
#include <sway/ui/controls/button/_typedefs.hpp>
#include <sway/ui/controls/button/button.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/item.hpp>
#include <sway/ui/widget/typedefs.hpp>

#include <memory>
#include <string>

namespace sway::ui {

class MenuItem : public Item {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  MenuItem(BuilderTypedefs::Ptr_t builder, const std::string &text);

  virtual ~MenuItem() = default;

  /** @} */
#pragma endregion

#pragma region "Overridden Item methods"

  MTHD_OVERRIDE(void update());

  MTHD_OVERRIDE(void repaint(PainterTypedefs::SharedPtr_t painter));

#pragma endregion

  void updateState();

  void focusGained();

  void focusLost();

private:
  ButtonTypedefs::SharedPtr_t button_;
};

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGET_MENUITEM_HPP
