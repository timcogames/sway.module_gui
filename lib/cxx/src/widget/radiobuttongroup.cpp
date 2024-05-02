#include <sway/ui/builder.hpp>
#include <sway/ui/widget/radiobutton.hpp>
#include <sway/ui/widget/radiobuttongroup.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

RadioButtonGroup::RadioButtonGroup(Builder *builder, LinearLayoutOrientation orientation)
    : LinearLayout(builder, orientation) {}

void RadioButtonGroup::deselect() {
  for (auto const &child : this->getChildNodes()) {
    std::static_pointer_cast<RadioButton>(child)->setChecked(false);
  }
}

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
