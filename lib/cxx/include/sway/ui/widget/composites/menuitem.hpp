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

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

class Builder;

NAMESPACE_BEGIN(widget)

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

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_MENUITEM_HPP
