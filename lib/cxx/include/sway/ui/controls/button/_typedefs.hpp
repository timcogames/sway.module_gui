#ifndef SWAY_UI_BUTTON_TYPEDEFS_HPP
#define SWAY_UI_BUTTON_TYPEDEFS_HPP

#include <sway/ui/_stdafx.hpp>

namespace sway::ui {

class Button;
class ToggleButton;
class RadioButton;
class RadioButtonGroup;

using ButtonSharedPtr_t = std::shared_ptr<Button>;
using ToggleButtonSharedPtr_t = std::shared_ptr<ToggleButton>;
using RadioButtonSharedPtr_t = std::shared_ptr<RadioButton>;
using RadioButtonOptionalSharedPtr_t = std::optional<RadioButtonSharedPtr_t>;
using RadioButtonGroupPtr_t = RadioButtonGroup *;
using RadioButtonGroupSharedPtr_t = std::shared_ptr<RadioButtonGroup>;

}  // namespace sway::ui

#endif  // SWAY_UI_BUTTON_TYPEDEFS_HPP
