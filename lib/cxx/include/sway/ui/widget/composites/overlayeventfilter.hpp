#ifndef SWAY_UI_WIDGET_OVERLAYEVENTFILTER_HPP
#define SWAY_UI_WIDGET_OVERLAYEVENTFILTER_HPP

#include <sway/core.hpp>

#include <memory>
#include <string>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class OverlayEventFilter : public core::evts::EventHandler {
public:
#pragma region "Ctors/Dtor"

  OverlayEventFilter() {}

  DTOR_VIRTUAL_DEFAULT(OverlayEventFilter);

#pragma endregion

#pragma region "Overridden EventHandler methods"

  MTHD_OVERRIDE(auto invoke(const core::foundation::Event::UniquePtr_t &evt) -> bool) final { return true; }

#pragma endregion
};

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGET_OVERLAYEVENTFILTER_HPP
