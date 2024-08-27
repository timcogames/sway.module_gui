#ifndef SWAY_UI_WIDGET_OVERLAYEVENTFILTER_HPP
#define SWAY_UI_WIDGET_OVERLAYEVENTFILTER_HPP

#include <sway/core.hpp>

#include <memory>
#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class OverlayEventFilter : public core::evts::EventHandler {
public:
#pragma region "Ctors/Dtor"

  OverlayEventFilter() {}

  virtual ~OverlayEventFilter() override = default;

#pragma endregion

#pragma region "Override EventHandler methods"

  MTHD_OVERRIDE(auto invoke(const core::foundation::Event::UniquePtr_t &evt) -> bool) final { return true; }

#pragma endregion
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_OVERLAYEVENTFILTER_HPP
