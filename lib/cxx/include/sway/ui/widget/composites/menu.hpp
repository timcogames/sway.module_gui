#ifndef SWAY_UI_WIDGET_MENU_HPP
#define SWAY_UI_WIDGET_MENU_HPP

#include <sway/core.hpp>
#include <sway/ui/orientations.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/menueventhandler.hpp>
#include <sway/ui/widget/composites/menuitem.hpp>
#include <sway/ui/widget/linearlayout.hpp>

#include <memory>
#include <string>
#include <unordered_map>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class Menu : public LinearLayout {
public:
  using Ptr_t = Menu *;
  using SharedPtr_t = std::shared_ptr<Menu>;

#pragma region "Ctors/Dtor"

  Menu(BuilderPtr_t builder, Orientation orien);

  virtual ~Menu();

#pragma endregion

#pragma region "Override Widget methods"

  MTHD_OVERRIDE(void update());

  MTHD_OVERRIDE(void repaint(Painter::SharedPtr_t painter));

#pragma endregion

  void addItem(const std::string &text);

private:
  core::evts::EventBus::Subscriber_t subscriber_;
  int selectedItem_;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_MENU_HPP
