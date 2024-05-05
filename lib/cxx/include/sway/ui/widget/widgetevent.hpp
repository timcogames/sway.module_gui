#ifndef SWAY_UI_WIDGET_WIDGETEVENT_HPP
#define SWAY_UI_WIDGET_WIDGETEVENT_HPP

#include <sway/core.hpp>
#include <sway/ui/widget/widgeteventtypes.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

struct PointerEnterEventData : public core::foundation::EventData {
  // clang-format off
  MTHD_OVERRIDE(auto serialize() const -> std::string) { return ""; }  // clang-format on

  MTHD_OVERRIDE(void deserialize(const std::string &jdata)) {}
};

struct PointerLeaveEventData : public core::foundation::EventData {
  // clang-format off
  MTHD_OVERRIDE(auto serialize() const -> std::string) { return ""; }  // clang-format on

  MTHD_OVERRIDE(void deserialize(const std::string &jdata)) {}
};

struct MouseClickEventData : public core::foundation::EventData {
  core::container::NodeIdx nodeidx;

  // clang-format off
  MTHD_OVERRIDE(auto serialize() const -> std::string) { return ""; }  // clang-format on

  MTHD_OVERRIDE(void deserialize(const std::string &jdata)) {}
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_WIDGETEVENT_HPP
