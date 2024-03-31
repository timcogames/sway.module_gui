#ifndef SWAY_UI_WIDGET_LABEL_HPP
#define SWAY_UI_WIDGET_LABEL_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/widget.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class Label : public Widget {
public:
  Label(Builder *builder, const std::string &text);

  virtual ~Label() = default;

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void paintEvent(std::shared_ptr<Painter> painter));

  void setText(const std::string &text);

  void setFont(const std::string &font);

  void setFontSize(int size);

private:
  std::string text_;
  std::string font_;
  int fontSize_;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_LABEL_HPP
