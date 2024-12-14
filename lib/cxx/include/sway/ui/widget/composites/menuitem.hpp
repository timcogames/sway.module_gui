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

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class MenuItem : public Item {
  DECLARE_PTR_ALIASES(MenuItem)

public:
#pragma region "Ctors/Dtor"

  MenuItem(BuilderTypedefs::Ptr_t builder, const std::string &text);

  DTOR_VIRTUAL_DEFAULT(MenuItem);

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

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGET_MENUITEM_HPP
