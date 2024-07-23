#ifndef SWAY_UI_WIDGET_ELEMENTBOXAREA_HPP
#define SWAY_UI_WIDGET_ELEMENTBOXAREA_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ui/widget/elementboxareatypes.hpp>

#include <array>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

struct ElementBoxArea {
  ElementBoxAreaType type;
  std::array<f32_t, core::detail::toBase(math::RectEdge::Latest)> edges;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_ELEMENTBOXAREA_HPP
