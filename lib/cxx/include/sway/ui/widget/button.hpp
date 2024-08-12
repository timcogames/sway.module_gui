#ifndef SWAY_UI_WIDGET_BUTTON_HPP
#define SWAY_UI_WIDGET_BUTTON_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/label.hpp>

#include <memory>
#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class Button : public Widget {
public:
  using Ptr_t = Button *;
  using SharedPtr_t = std::shared_ptr<Button>;

#pragma region "Ctors/Dtor"

  Button(Builder *builder, const std::string &text);

  virtual ~Button() = default;

#pragma endregion

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void repaint(Painter::SharedPtr_t painter));

  auto getLabel() const -> Label::SharedPtr_t { return label_; }

private:
  Label::SharedPtr_t label_;
  bool hovering_;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_BUTTON_HPP
