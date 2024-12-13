#ifndef SWAY_UI_BUTTON_HPP
#define SWAY_UI_BUTTON_HPP

#include <sway/core.hpp>
#include <sway/ui/controls/button/button.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/label.hpp>

#include <memory>
#include <string>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class Button : public Widget {
  DECLARE_PTR_ALIASES(Button)

public:
#pragma region "Ctors/Dtor"

  Button(BuilderTypedefs::Ptr_t builder, const std::string &text);

  DTOR_VIRTUAL(Button);

#pragma endregion

#pragma region "Overridden Widget methods"

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void repaint(PainterTypedefs::SharedPtr_t painter));

#pragma endregion

  auto getLabel() const -> Label::SharedPtr_t { return labelWidget_; }

private:
  Label::SharedPtr_t labelWidget_;
  bool hovering_;
};

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_BUTTON_HPP
