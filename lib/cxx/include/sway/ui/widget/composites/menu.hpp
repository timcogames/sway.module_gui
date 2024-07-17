#ifndef SWAY_UI_WIDGET_MENU_HPP
#define SWAY_UI_WIDGET_MENU_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/menuitem.hpp>

#include <string>
#include <vector>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class Menu : public LinearLayout {
public:
  using ItemList_t = std::vector<std::string>;

#pragma region "Ctors/Dtor"

  Menu(Builder::Ptr_t builder, std::initializer_list<std::string> items)
      : items_(items) {}

  virtual ~Menu() = default;

#pragma endregion

#pragma region "Override Widget methods"

  MTHD_OVERRIDE(void update()) {}

  MTHD_OVERRIDE(void paintEvent(Painter::SharedPtr_t painter)) {}

#pragma endregion

  void addItem(const std::string &item) { items_.push_back(item); }

  void clear() { items_.clear(); }

private:
  ItemList_t items_;
  int selectedItem_;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_MENU_HPP
