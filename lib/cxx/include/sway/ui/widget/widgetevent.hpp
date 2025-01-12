#ifndef SWAY_UI_WIDGET_WIDGETEVENT_HPP
#define SWAY_UI_WIDGET_WIDGETEVENT_HPP

#include <sway/core.hpp>
#include <sway/ui/widget/widgeteventtypes.hpp>

namespace sway::ui {

struct PointerEnterEventData : public core::EventData {
  // MTHD_OVERRIDE(auto serialize() const -> std::string) { return ""; }

  // MTHD_OVERRIDE(void deserialize(const std::string &jdata)) {}
};

struct PointerLeaveEventData : public core::EventData {
  // MTHD_OVERRIDE(auto serialize() const -> std::string) { return ""; }

  // MTHD_OVERRIDE(void deserialize(const std::string &jdata)) {}
};

struct MouseClickEventData : public core::EventData {
  core::NodeIndex nodeidx;
  u32_t state;

  // MTHD_OVERRIDE(auto serialize() const -> std::string) { return ""; }

  // MTHD_OVERRIDE(void deserialize(const std::string &jdata)) {}
};

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGET_WIDGETEVENT_HPP
