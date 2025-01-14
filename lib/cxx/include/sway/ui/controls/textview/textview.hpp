#ifndef SWAY_UI_TEXTVIEW_HPP
#define SWAY_UI_TEXTVIEW_HPP

#include <sway/ui/_stdafx.hpp>
#include <sway/ui/controls/textview/_typedefs.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/typography.hpp>
#include <sway/ui/widget/typedefs.hpp>
#include <sway/ui/widget/widget.hpp>

namespace sway::ui {

class TextView : public Widget {
public:
#pragma region "Pointer aliases"
  /** \~english @name Pointer aliases */ /** \~russian @name Типы указателей */
  /** @{ */

  using SharedPtr_t = TextViewSharedPtr_t;

  /** @} */
#pragma endregion

#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  TextView(BuilderPtr_t builder, const std::string &text);

  virtual ~TextView() = default;

  /** @} */
#pragma endregion

#pragma region "Overridden Widget methods"

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void repaint(PainterSharedPtr_t painter));

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

}  // namespace sway::ui

#endif  // SWAY_UI_TEXTVIEW_HPP
