#ifndef SWAY_UI_WIDGET_BUTTON_HPP
#define SWAY_UI_WIDGET_BUTTON_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/label.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class Button : public Widget {
public:
  Button(Builder *builder, const std::string &text);

  virtual ~Button() = default;

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void paintEvent(std::shared_ptr<Painter> painter));

private:
  std::shared_ptr<Label> label_;
  bool hovering_;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_BUTTON_HPP
