#ifndef SWAY_UI_ELEMENT_EVENTHUBS_MOUSEEVENT_HPP
#define SWAY_UI_ELEMENT_EVENTHUBS_MOUSEEVENT_HPP

#include <sway/ui/_stdafx.hpp>
#include <sway/ui/element/event/_typedefs.hpp>
#include <sway/ui/element/event/specs/inputevent.hpp>

namespace sway::ui {

class MouseEvent : public InputEvent {
protected:
  explicit MouseEvent(
      u32_t type, const core::v2::EventContext &context, u32_t modifiers, u32_t state, const math::point2f_t &point)
      : InputEvent(type, context, modifiers)
      , state_(state)
      , point_(point) {}

public:
  static auto create(u32_t type, const core::v2::EventContext &context) -> MouseEvent *;

  virtual ~MouseEvent() = default;

  [[nodiscard]] auto getState() const -> u32_t { return state_; }

  [[nodiscard]] auto getPoint() const -> const math::point2f_t & { return point_; }

private:
  u32_t state_;
  math::point2f_t point_;
};

}  // namespace sway::ui

#endif  // SWAY_UI_ELEMENT_EVENTHUBS_MOUSEEVENT_HPP
