#ifndef SWAY_UI_WIDGET_BUTTON_HPP
#define SWAY_UI_WIDGET_BUTTON_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/button.hpp>
#include <sway/ui/widget/label.hpp>

#include <memory>
#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class Button : public Widget {
  DECLARE_CLASS_POINTER_ALIASES(Button)

public:
#pragma region "Ctors/Dtor"

  Button(BuilderPtr_t builder, const std::string &text);

  virtual ~Button() = default;

#pragma endregion

#pragma region "Override Widget methods"

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void repaint(Painter::SharedPtr_t painter));

#pragma endregion

  auto getLabel() const -> Label::SharedPtr_t { return labelWidget_; }

private:
  Label::SharedPtr_t labelWidget_;
  bool hovering_;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_BUTTON_HPP
