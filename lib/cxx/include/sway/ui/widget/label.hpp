#ifndef SWAY_UI_WIDGET_LABEL_HPP
#define SWAY_UI_WIDGET_LABEL_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/typography.hpp>
#include <sway/ui/widget/widget.hpp>

#include <memory>
#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class Label : public Widget {
public:
  using Ptr_t = Label *;
  using SharedPtr_t = std::shared_ptr<Label>;

#pragma region "Ctors/Dtor"

  Label(BuilderPtr_t builder, const std::string &text);

  virtual ~Label() = default;

#pragma endregion

#pragma region "Override Widget methods"

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void repaint(Painter::SharedPtr_t painter));

#pragma endregion

  void resize();

  void setText(const std::string &text);

  void setFont(const std::string &font);

  void setFontSize(int size);

private:
  std::string text_;
  std::string font_;

  int fontSize_;
  typography::col_t fontColor_;

  // int lineSpacing_;
  // math::col4f_t fontShadowColor_;
  // bool uppercase_;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_LABEL_HPP
