#ifndef SWAY_UI_BUTTON_HPP
#define SWAY_UI_BUTTON_HPP

#include <sway/ui/_stdafx.hpp>
#include <sway/ui/controls/button/_typedefs.hpp>
#include <sway/ui/controls/textview/_typedefs.hpp>
#include <sway/ui/controls/textview/textview.hpp>
#include <sway/ui/painter.hpp>

namespace sway::ui {

class Button : public Widget {
public:
#pragma region "Static methods"
  /** \~english @name Creators */ /** \~russian @name Создатели */
  /** @{ */

  static auto create(BuilderPtr_t builder, const std::string &text) -> ButtonSharedPtr_t;

  /** @} */
#pragma endregion

#pragma region "Define aliases"
  /** \~english @name Define aliases */ /** \~russian @name Определение алиасов */
  /** @{ */

  using SharedPtr_t = ButtonSharedPtr_t;

  /** @} */
#pragma endregion

#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  Button(BuilderPtr_t builder, const std::string &text);

  virtual ~Button();

  /** @} */
#pragma endregion

  void updateState();

#pragma region "Overridden Widget methods"

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void repaint(PainterSharedPtr_t painter));

#pragma endregion

  auto getLabel() const -> TextViewSharedPtr_t { return textView_; }

private:
  TextViewSharedPtr_t textView_;
  bool hovering_;
};

}  // namespace sway::ui

#endif  // SWAY_UI_BUTTON_HPP
