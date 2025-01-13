#ifndef SWAY_UI_ELEMENT_TYPEDEFS_HPP
#define SWAY_UI_ELEMENT_TYPEDEFS_HPP

#include <sway/ui/_stdafx.hpp>

namespace sway::ui {

class Element;

using ElementPtr_t = Element *;
using ElementSharedPtr_t = std::shared_ptr<Element>;

using ElementUnderPointer_t = ElementPtr_t;

}  // namespace sway::ui

#endif  // SWAY_UI_ELEMENT_TYPEDEFS_HPP
