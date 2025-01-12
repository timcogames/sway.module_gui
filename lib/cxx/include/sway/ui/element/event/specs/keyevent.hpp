#ifndef SWAY_UI_ELEMENT_EVENTHUBS_KEYEVENT_HPP
#define SWAY_UI_ELEMENT_EVENTHUBS_KEYEVENT_HPP

#include <sway/core.hpp>
#include <sway/ui/element/event/_typedefs.hpp>
#include <sway/ui/element/event/specs/inputevent.hpp>

namespace sway::ui {

class KeyEvent : public InputEvent {
protected:
  explicit KeyEvent(
      u32_t type, const core::v2::EventContext &context, u32_t modifiers, u32_t keyCode, const std::string &utf8)
      : InputEvent(type, context, modifiers)
      , keyCode_(keyCode)
      , utf8_(std::move(utf8)) {}

public:
  virtual ~KeyEvent() = default;

  [[nodiscard]] auto getKeyCode() const -> u32_t { return keyCode_; }

  [[nodiscard]] auto getUtf8() const -> const std::string & { return utf8_; }

private:
  u32_t keyCode_;
  std::string utf8_;
};

}  // namespace sway::ui

#endif  // SWAY_UI_ELEMENT_EVENTHUBS_KEYEVENT_HPP
