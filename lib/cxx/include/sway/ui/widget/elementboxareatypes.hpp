#ifndef SWAY_UI_WIDGET_ELEMENTBOXAREATYPES_HPP
#define SWAY_UI_WIDGET_ELEMENTBOXAREATYPES_HPP

#include <sway/core.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

enum class ElementBoxAreaType : u32_t { AUTO, MARGIN, BORDER, PADDING, CONTENT, Latest };

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_ELEMENTBOXAREATYPES_HPP