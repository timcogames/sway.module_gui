#ifndef SWAY_UI_ELEMRNT_EVENTHUBS_BUTTONEVENT_HPP
#define SWAY_UI_ELEMRNT_EVENTHUBS_BUTTONEVENT_HPP

#include <sway/core.hpp>
#include <sway/core/events/v2/event.hpp>
#include <sway/ui/element/event/_typedefs.hpp>

namespace sway::ui {

class ButtonEvent : public core::v2::Event {
protected:
  explicit ButtonEvent(u32_t type, const core::v2::EventContext &context, u32_t button)
      : core::v2::Event(type, context)
      , button_(button) {}

public:
  virtual ~ButtonEvent() = default;

  [[nodiscard]] auto getButton() const -> u32_t { return button_; }

private:
  u32_t button_;
};

}  // namespace sway::ui

#endif  // SWAY_UI_ELEMRNT_EVENTHUBS_BUTTONEVENT_HPP
