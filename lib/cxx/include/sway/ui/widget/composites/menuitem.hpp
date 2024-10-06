#ifndef SWAY_UI_WIDGET_MENUITEM_HPP
#define SWAY_UI_WIDGET_MENUITEM_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/button.hpp>
#include <sway/ui/widget/composites/item.hpp>
#include <sway/ui/widget/typedefs.hpp>

#include <memory>
#include <string>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class Builder;

NS_BEGIN(widget)

class MenuItem : public Item {
  DECLARE_CLASS_POINTER_ALIASES(MenuItem)

public:
#pragma region "Ctors/Dtor"

  MenuItem(BuilderPtr_t builder, const std::string &text);

  virtual ~MenuItem() = default;

#pragma endregion

#pragma region "Override Item methods"

  MTHD_OVERRIDE(void update());

  MTHD_OVERRIDE(void repaint(Painter::SharedPtr_t painter));

#pragma endregion

  void updateState();

  void focusGained();

  void focusLost();

private:
  Button::SharedPtr_t button_;
};

NS_END()  // namespace widget
NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGET_MENUITEM_HPP
