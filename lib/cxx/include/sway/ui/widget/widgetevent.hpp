#ifndef SWAY_UI_WIDGET_WIDGETEVENT_HPP
#define SWAY_UI_WIDGET_WIDGETEVENT_HPP

#include <sway/core.hpp>
#include <sway/ui/widget/widgeteventtypes.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

struct PointerEnterEventData : public core::foundation::EventData {
  MTHD_OVERRIDE(auto serialize() const -> std::string) { return ""; }

  MTHD_OVERRIDE(void deserialize(const std::string &jdata)) {}
};

struct PointerLeaveEventData : public core::foundation::EventData {
  MTHD_OVERRIDE(auto serialize() const -> std::string) { return ""; }

  MTHD_OVERRIDE(void deserialize(const std::string &jdata)) {}
};

struct MouseClickEventData : public core::foundation::EventData {
  core::container::NodeIdx nodeidx;
  u32_t state;

  MTHD_OVERRIDE(auto serialize() const -> std::string) { return ""; }

  MTHD_OVERRIDE(void deserialize(const std::string &jdata)) {}
};

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGET_WIDGETEVENT_HPP
