#ifndef SWAY_UI_ELEMENT_EVENTHUBS_DATAEVENT_HPP
#define SWAY_UI_ELEMENT_EVENTHUBS_DATAEVENT_HPP

#include <sway/core.hpp>
#include <sway/core/events/v2/event.hpp>
#include <sway/ui/element/event/_typedefs.hpp>

namespace sway::ui {

class DataEvent : public core::v2::Event {
protected:
  explicit DataEvent(u32_t type, const core::v2::EventContext &context, const std::string &data, u32_t source)
      : core::v2::Event(type, context)
      , data_(std::move(data))
      , source_(source) {}

public:
  virtual ~DataEvent() = default;

  [[nodiscard]] auto getData() const -> const std::string & { return data_; }

  [[nodiscard]] auto getSource() const -> u32_t { return source_; }

private:
  std::string data_;
  u32_t source_;
};

}  // namespace sway::ui

#endif  // SWAY_UI_ELEMENT_EVENTHUBS_DATAEVENT_HPP
