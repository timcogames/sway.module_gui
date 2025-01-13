#ifndef SWAY_UI_WIDGET_OVERLAYEVENTFILTER_HPP
#define SWAY_UI_WIDGET_OVERLAYEVENTFILTER_HPP

#include <sway/ui/_stdafx.hpp>

namespace sway::ui {

class OverlayEventFilter : public core::EventHandler {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  OverlayEventFilter()
      : core::EventHandler(nullptr) {}

  virtual ~OverlayEventFilter() = default;

  /** @} */
#pragma endregion

#pragma region "Overridden EventHandler methods"

  MTHD_OVERRIDE(auto invoke( core::EventTypedefs::UniquePtr_t &&evt) -> bool) final { return true; }

#pragma endregion
};

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGET_OVERLAYEVENTFILTER_HPP
