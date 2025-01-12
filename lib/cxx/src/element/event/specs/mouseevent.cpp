#include <sway/ui/element/event/specs/mouseevent.hpp>

namespace sway::ui {

auto MouseEvent::create(u32_t type, const core::v2::EventContext &context) -> MouseEvent * {
  auto *event = new MouseEvent(type, context, 0, 0, math::point2f_zero);
  return event;
}

}  // namespace sway::ui
