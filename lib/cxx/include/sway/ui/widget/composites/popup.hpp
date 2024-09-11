#ifndef SWAY_UI_WIDGET_POPUP_HPP
#define SWAY_UI_WIDGET_POPUP_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/draggable.hpp>
#include <sway/ui/widget/typedefs.hpp>

#include <memory>
#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class Popup : public Widget {
  DECLARE_CLASS_POINTER_ALIASES(Popup)

public:
#pragma region "Ctors/Dtor"

  Popup(BuilderPtr_t builder);

  virtual ~Popup();

#pragma endregion

#pragma region "Override Widget methods"

  MTHD_OVERRIDE(void update());

  MTHD_OVERRIDE(void repaint(Painter::SharedPtr_t painter));

#pragma endregion

private:
  core::evts::EventBus::Subscriber_t subscriber_;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_POPUP_HPP
