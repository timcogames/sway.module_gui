#ifndef SWAY_UI_TEXTVIEW_HPP
#define SWAY_UI_TEXTVIEW_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/typography.hpp>
#include <sway/ui/widget/typedefs.hpp>
#include <sway/ui/widget/widget.hpp>

#include <memory>
#include <string>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class TextView : public Widget {
public:
#pragma region "Ctors/Dtor"

  TextView(BuilderTypedefs::Ptr_t builder, const std::string &text);

  DTOR_VIRTUAL_DEFAULT(TextView);

#pragma endregion

#pragma region "Overridden Widget methods"

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void repaint(PainterTypedefs::SharedPtr_t painter));

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

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_TEXTVIEW_HPP
