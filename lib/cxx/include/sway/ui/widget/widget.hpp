#ifndef SWAY_UI_WIDGET_WIDGET_HPP
#define SWAY_UI_WIDGET_WIDGET_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ois.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/appearance.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

#define COL4F_RED math::col4f_t(0.85F, 0.33F, 0.17F, 1.0F)
#define COL4F_GREEN math::col4f_t(0.5F, 0.6F, 0.43F, 1.0F)
#define COL4F_BLUE math::col4f_t(0.4F, 0.53F, 0.56F, 1.0F)
#define COL4F_BEIGE math::col4f_t(0.81F, 0.75F, 0.68F, 1.0F)
#define COL4F_GRAY1 math::col4f_t(0.1F, 0.1F, 0.1F, 1.0F)
#define COL4F_GRAY2 math::col4f_t(0.18F, 0.17F, 0.16F, 1.0F)

class Builder;

NAMESPACE_BEGIN(widget)

enum class WidgetEventType : u32_t { MOUSE_OVER = 50, MOUSE_OUT, POINTER_ENTER, POINTER_LEAVE };

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
  std::string uid;

  // clang-format off
  MTHD_OVERRIDE(auto serialize() const -> std::string) { return ""; }  // clang-format on

  MTHD_OVERRIDE(void deserialize(const std::string &jdata)) {}
};

class Widget : public core::container::Node {
public:
  DECLARE_EVENT(EVT_POINTER_ENTER, PointerEnter)
  DECLARE_EVENT(EVT_POINTER_LEAVE, PointerLeave)
  DECLARE_EVENT(EVT_MOUSE_CLICKED, MouseClicked)

  Widget(Builder *builder);

  virtual ~Widget() = default;

  MTHD_VIRTUAL(void onCursorPointerEnter());

  MTHD_VIRTUAL(void onCursorPointerLeave());

  MTHD_VIRTUAL(void onMouseClick());

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

  [[nodiscard]]
  auto getSize() const -> math::size2f_t;

  void setMargin(const math::Margin<f32_t> &margin);

  [[nodiscard]]
  auto getMargin() const -> math::Margin<f32_t>;

  void setBackgroundColor(const math::col4f_t &col);

  [[nodiscard]]
  auto getBackgroundColor() const -> math::col4f_t;

  void setForegroundColor(const math::col4f_t &col);

  [[nodiscard]]
  auto getForegroundColor() const -> math::col4f_t;

  auto getChildAtPoint(const math::point2f_t &point) -> Widget *;

  // wdt/hgt, margin, border, padding
  auto getOuterSize() const -> math::size2f_t {
    const auto size = this->getSize();
    const auto outerWdt = size.getW() + margin_.getLR();
    const auto outerHgt = size.getH() + margin_.getTB();

    return math::size2f_t(outerWdt, outerHgt);
  }

  void setMouseFilter(ois::MouseFilter filter) { mouseFilter_ = filter; }

  [[nodiscard]]
  auto getMouseFilter() const -> ois::MouseFilter {
    return mouseFilter_;
  }

  void setAlignment(math::Alignment alignment) { alignment_ = alignment; }

protected:
  Builder *builder_;
  ois::MouseFilter mouseFilter_;
  math::rect4f_t rect_;
  // math::rect4f_t innerRect_;  // wdt/hgt, padding
  // math::rect4f_t outerRect_;  // wdt/hgt, margin, border, padding
  math::Margin<f32_t> margin_;
  // math::Margin<f32_t> padd_;
  math::Alignment alignment_;
  Appearance appearance_;

  bool containsPointer_;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_WIDGET_HPP
