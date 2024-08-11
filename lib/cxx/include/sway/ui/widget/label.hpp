#ifndef SWAY_UI_WIDGET_LABEL_HPP
#define SWAY_UI_WIDGET_LABEL_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/widget.hpp>

#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class Label : public Widget {
public:
#pragma region "Ctors/Dtor"

  Label(Builder::Ptr_t builder, const std::string &text);

  virtual ~Label() = default;

#pragma endregion

#pragma region "Override Widget methods"

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void paintEvent(Painter::SharedPtr_t painter));

#pragma endregion

  void resize();

  void setText(const std::string &text);

  void setFont(const std::string &font);

  void setFontSize(int size);

private:
  std::string text_;
  std::string font_;

  int fontSize_;
  math::col4f_t fontColor_;

  // int lineSpacing_;
  // math::col4f_t fontShadowColor_;
  // bool uppercase_;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_LABEL_HPP
