#ifndef SWAY_UI_BUTTON_TYPEDEFS_HPP
#define SWAY_UI_BUTTON_TYPEDEFS_HPP

#include <sway/core.hpp>

#include <array>

namespace sway::ui {

class Button;
namespace ButtonTypedefs {
using SharedPtr_t = std::shared_ptr<Button>;
}  // namespace ButtonTypedefs

class RadioButton;
namespace RadioButtonTypedefs {
using SharedPtr_t = std::shared_ptr<RadioButton>;
using OptionalSharedPtr_t = std::optional<SharedPtr_t>;
}  // namespace RadioButtonTypedefs

}  // namespace sway::ui

#endif  // SWAY_UI_BUTTON_TYPEDEFS_HPP
