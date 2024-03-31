#ifndef SWAY_UI_WIDGET_WIDGET_HPP
#define SWAY_UI_WIDGET_WIDGET_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/appearance.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

class Builder;

NAMESPACE_BEGIN(widget)

enum class WidgetEventType : u32_t { MOUSE_OVER = 50, MOUSE_OUT, POINTER_ENTER, POINTER_LEAVE };

struct WidgetEventData : core::foundation::EventData {
  std::string uid;

  WidgetEventData() {}

  // clang-format off
  MTHD_OVERRIDE(auto serialize() const -> std::string) {  // clang-format on
    return "";
  }

  MTHD_OVERRIDE(void deserialize(const std::string &jdata)) {}
};

class WidgetEvent : public core::foundation::Event {
public:
  DECLARE_CLASS_METADATA(WidgetEvent, core::foundation::Event)

  WidgetEvent(u32_t type, core::foundation::EventData *data)
      : id_(core::misc::newGuid<UUID_NBR_OF_GROUPS>(UUID_MAGIC))
      , type_(type)
      , data_(data) {}

  ~WidgetEvent() = default;

  // clang-format off
  MTHD_OVERRIDE(auto id() const -> std::string) {  // clang-format on
    return id_;
  }

  // clang-format off
  MTHD_OVERRIDE(auto type() const -> u32_t) {  // clang-format on
    return type_;
  }

  // clang-format off
  MTHD_OVERRIDE(auto data() const -> core::foundation::EventData *) {  // clang-format on
    return data_;
  }

private:
  std::string id_;
  u32_t type_;
  core::foundation::EventData *data_;
};

class Widget : public core::container::Node {
public:
  Widget(Builder *builder);

  virtual ~Widget() = default;

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void paintEvent(std::shared_ptr<Painter> painter));

  void setRect(const math::rect4f_t &rect);

  [[nodiscard]]
  auto getRect() const -> math::rect4f_t;

  [[nodiscard]]
  auto hasRelated() -> bool;

  void setPosition(const math::vec2f_t &pos);

  [[nodiscard]]
  auto getPosition() const -> math::point2f_t;

  void setSize(const math::size2f_t &size);

  void setBackgroundColor(const math::col4f_t &col);

  [[nodiscard]]
  auto getBackgroundColor() const -> math::col4f_t;

  void setForegroundColor(const math::col4f_t &col);

  [[nodiscard]]
  auto getForegroundColor() const -> math::col4f_t;

  void setVisible(bool val);

  [[nodiscard]]
  auto hasVisible() const -> bool;

  auto getChildAt(const math::point2f_t &point) -> Widget *;

  void setHover(bool val);

  auto hasHovered() -> bool { return hovered_; }

protected:
  Builder *builder_;
  math::rect4f_t rect_;

  Appearance appearance_;

  bool visibled_;
  bool hovered_;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_WIDGET_HPP
