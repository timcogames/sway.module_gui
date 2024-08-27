#ifndef SWAY_UI_WIDGET_OVERLAY_HPP
#define SWAY_UI_WIDGET_OVERLAY_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/widget.hpp>

#include <memory>
#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class Overlay : public Widget {
public:
  using Ptr_t = Overlay *;
  using SharedPtr_t = std::shared_ptr<Overlay>;

#pragma region "Ctors/Dtor"

  Overlay(BuilderPtr_t builder);

  virtual ~Overlay();

#pragma endregion

#pragma region "Override Widget methods"

  MTHD_OVERRIDE(void update());

  MTHD_OVERRIDE(void repaint(Painter::SharedPtr_t painter));

#pragma endregion
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_OVERLAY_HPP
