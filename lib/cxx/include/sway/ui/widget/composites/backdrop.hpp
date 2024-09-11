#ifndef SWAY_UI_WIDGET_BACKDROP_HPP
#define SWAY_UI_WIDGET_BACKDROP_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/typedefs.hpp>
#include <sway/ui/widget/widget.hpp>

#include <memory>
#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

// pseudo-element
class Backdrop : public Widget {
  DECLARE_CLASS_POINTER_ALIASES(Backdrop)

public:
#pragma region "Ctors/Dtor"

  Backdrop(BuilderPtr_t builder);

  virtual ~Backdrop();

#pragma endregion

#pragma region "Override Widget methods"

  MTHD_OVERRIDE(void update());

  MTHD_OVERRIDE(void repaint(Painter::SharedPtr_t painter));

#pragma endregion
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_BACKDROP_HPP
