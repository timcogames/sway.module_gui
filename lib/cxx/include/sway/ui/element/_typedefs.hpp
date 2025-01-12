#ifndef SWAY_UI_ELEMENT_TYPEDEFS_HPP
#define SWAY_UI_ELEMENT_TYPEDEFS_HPP

#include <sway/core.hpp>

namespace sway::ui {

class Element;
namespace ElementTypedefs {
using Ptr_t = Element *;
using SharedPtr_t = std::shared_ptr<Element>;
using UnderPointer_t = Ptr_t;
}  // namespace ElementTypedefs

}  // namespace sway::ui

#endif  // SWAY_UI_ELEMENT_TYPEDEFS_HPP
