#ifndef SWAY_UI_WIDGET_MENUITEM_HPP
#define SWAY_UI_WIDGET_MENUITEM_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/label.hpp>

#include <memory>
#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class MenuItem : public Widget {
public:
  using Ptr_t = MenuItem *;
  using SharedPtr_t = std::shared_ptr<MenuItem>;

#pragma region "Ctors/Dtor"

  MenuItem(Builder::Ptr_t builder) {}

  virtual ~MenuItem() = default;

#pragma endregion

#pragma region "Override Widget methods"

  MTHD_OVERRIDE(void update()) {
    auto y = 1.f;
    auto color = (u8_t)std::floor(255.f * ((y > 1.f) ? (2.f - y) : (y)));
    this->setForegroundColor(COL4F_PURPLE | (color << 16));
  }

  MTHD_OVERRIDE(void paintEvent(Painter::SharedPtr_t painter)) {
    for (auto i = 0; i < items_.size(); ++i) {
      // items
    }
  }

#pragma endregion

private:
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_MENUITEM_HPP
