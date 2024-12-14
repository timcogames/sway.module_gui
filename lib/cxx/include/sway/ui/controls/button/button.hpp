#ifndef SWAY_UI_BUTTON_HPP
#define SWAY_UI_BUTTON_HPP

#include <sway/core.hpp>
#include <sway/ui/controls/button/_typedefs.hpp>
#include <sway/ui/controls/textview/_typedefs.hpp>
#include <sway/ui/controls/textview/textview.hpp>
#include <sway/ui/painter.hpp>

#include <memory>
#include <string>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class Button : public Widget {
public:
#pragma region "Static methods"

  /**
   * @name creators
   * @{
   */

  static auto create(BuilderTypedefs::Ptr_t builder, const std::string &text) -> ButtonTypedefs::SharedPtr_t;

  /**
   * end of creators group
   * @}
   */

#pragma endregion

#pragma region "Ctors/Dtor"

  Button(BuilderTypedefs::Ptr_t builder, const std::string &text);

  DTOR_VIRTUAL(Button);

#pragma endregion

  void updateState();

#pragma region "Overridden Widget methods"

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void repaint(PainterTypedefs::SharedPtr_t painter));

#pragma endregion

  auto getLabel() const -> TextViewTypedefs::SharedPtr_t { return textView_; }

private:
  TextViewTypedefs::SharedPtr_t textView_;
  bool hovering_;
};

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_BUTTON_HPP
