#ifndef SWAY_UI_WIDGET_MENU_HPP
#define SWAY_UI_WIDGET_MENU_HPP

#include <sway/core.hpp>
#include <sway/ui/orientations.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/menueventhandler.hpp>
#include <sway/ui/widget/composites/menuitem.hpp>
#include <sway/ui/widget/linearlayout.hpp>
#include <sway/ui/widget/typedefs.hpp>

#include <memory>
#include <string>
#include <unordered_map>

NS_BEGIN_SWAY()
NS_BEGIN(ui)
NS_BEGIN(widget)

class Menu : public LinearLayout {
  DECLARE_PTR_ALIASES(Menu)

public:
#pragma region "Ctors/Dtor"

  Menu(BuilderTypedefs::Ptr_t builder, Orientation orien);

  DTOR_VIRTUAL(Menu);

#pragma endregion

#pragma region "Overridden Widget methods"

  MTHD_OVERRIDE(void update());

  MTHD_OVERRIDE(void repaint(PainterTypedefs::SharedPtr_t painter));

#pragma endregion

  void addItem(const std::string &text);

private:
  core::evts::EventBus::Subscriber_t subscriber_;
  int selectedItem_;
};

NS_END()  // namespace widget
NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGET_MENU_HPP
