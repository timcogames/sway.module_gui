#ifndef SWAY_UI_TEXTVIEW_TYPEDEFS_HPP
#define SWAY_UI_TEXTVIEW_TYPEDEFS_HPP

#include <sway/core.hpp>

#include <array>

namespace sway::ui {

class TextView;
namespace TextViewTypedefs {
using SharedPtr_t = std::shared_ptr<TextView>;
}  // namespace TextViewTypedefs

}  // namespace sway::ui

#endif  // SWAY_UI_TEXTVIEW_TYPEDEFS_HPP
