#ifndef SWAY_UI_BUTTON_TYPEDEFS_HPP
#define SWAY_UI_BUTTON_TYPEDEFS_HPP

#include <sway/core.hpp>

#include <array>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class Button;
namespace ButtonTypedefs {
using SharedPtr_t = std::shared_ptr<Button>;
}  // namespace ButtonTypedefs

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_BUTTON_TYPEDEFS_HPP
