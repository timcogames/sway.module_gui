#ifndef SWAY_UI_WIDGET_BACKDROP_HPP
#define SWAY_UI_WIDGET_BACKDROP_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/typedefs.hpp>
#include <sway/ui/widget/widget.hpp>

#include <memory>
#include <string>

NS_BEGIN_SWAY()
NS_BEGIN(ui)
NS_BEGIN(widget)

// pseudo-element
class Backdrop : public Widget {
  DECLARE_PTR_ALIASES(Backdrop)

public:
#pragma region "Ctors/Dtor"

  Backdrop(BuilderPtr_t builder);

  DTOR_VIRTUAL(Backdrop);

#pragma endregion

#pragma region "Override Widget methods"

  MTHD_OVERRIDE(void update());

  MTHD_OVERRIDE(void repaint(Painter::SharedPtr_t painter));

#pragma endregion
};

NS_END()  // namespace widget
NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGET_BACKDROP_HPP
