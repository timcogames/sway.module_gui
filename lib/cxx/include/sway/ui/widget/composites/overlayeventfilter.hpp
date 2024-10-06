#ifndef SWAY_UI_WIDGET_OVERLAYEVENTFILTER_HPP
#define SWAY_UI_WIDGET_OVERLAYEVENTFILTER_HPP

#include <sway/core.hpp>

#include <memory>
#include <string>

NS_BEGIN_SWAY()
NS_BEGIN(ui)
NS_BEGIN(widget)

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

NS_END()  // namespace widget
NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGET_OVERLAYEVENTFILTER_HPP
