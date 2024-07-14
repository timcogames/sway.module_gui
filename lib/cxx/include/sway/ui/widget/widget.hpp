#ifndef SWAY_UI_WIDGET_WIDGET_HPP
#define SWAY_UI_WIDGET_WIDGET_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ois.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/appearance.hpp>
#include <sway/ui/widget/widgetevent.hpp>
#include <sway/ui/widget/widgeteventtypes.hpp>

#include <array>
#include <optional>

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

#define NUM_AREAS 3  // MARGIN, BORDER, PADDING
#define NUM_EDGES 4

enum class ElementBoxAreaType : u32_t { AUTO, MARGIN, BORDER, PADDING, CONTENT, Latest };

class ElementBox {
public:
  struct Area {
    ElementBoxAreaType type;
    std::array<f32_t, core::detail::toUnderlying(math::RectEdge::Latest)> edges;
  };

  ElementBox(const math::sizef_t &content)
      : content_(content) {}

  ~ElementBox() = default;

  auto getArea(ElementBoxAreaType type) const -> std::optional<Area> {
    std::optional<Area> area = std::nullopt;
    for (const auto item : areas_) {
      if (item.has_value() && item.value().type == type) {
        area = item;
      }
    }

    return area;
  }

  auto getPosition(ElementBoxAreaType type) const -> math::vec2f_t {
    auto result = math::vec2f_zero;

    auto mgn = this->getArea(ElementBoxAreaType::MARGIN);
    if (!mgn.has_value()) {
    } else {
      result = math::vec2f_t(-std::get<core::detail::toUnderlying(math::RectEdge::IDX_L)>(mgn.value().edges),
          -std::get<core::detail::toUnderlying(math::RectEdge::IDX_T)>(mgn.value().edges));
    }

    auto brd = this->getArea(ElementBoxAreaType::BORDER);
    if (!brd.has_value()) {
    } else {
      result =
          math::vec2f_t(result.getX() + std::get<core::detail::toUnderlying(math::RectEdge::IDX_L)>(brd.value().edges),
              result.getY() + std::get<core::detail::toUnderlying(math::RectEdge::IDX_T)>(brd.value().edges));
    }

    auto pad = this->getArea(ElementBoxAreaType::PADDING);
    if (!pad.has_value()) {
    } else {
      result =
          math::vec2f_t(result.getX() + std::get<core::detail::toUnderlying(math::RectEdge::IDX_L)>(pad.value().edges),
              result.getY() + std::get<core::detail::toUnderlying(math::RectEdge::IDX_T)>(pad.value().edges));
    }

    return result;
  }

private:
  math::sizef_t content_;
  std::array<std::optional<Area>, NUM_AREAS> areas_;
};

class Widget : public core::container::Node {
public:
  DECLARE_EVENT(EVT_POINTER_ENTER, PointerEnter)
  DECLARE_EVENT(EVT_POINTER_LEAVE, PointerLeave)
  DECLARE_EVENT(EVT_MOUSE_CLICKED, MouseClicked)

  // DECLARE_EVENT(EVT_PRESSED, Pressed)
  // DECLARE_EVENT(EVT_RELEASED, Released)
  // DECLARE_EVENT(EVT_CLICKED, Clicked)
  // DECLARE_EVENT(EVT_ENTER, Enter)
  // DECLARE_EVENT(EVT_LEAVE, Leave)
  // DECLARE_EVENT(EVT_ACTIVATE, Activate)

  Widget(Builder *builder);

  virtual ~Widget() = default;

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void paintEvent(std::shared_ptr<Painter> painter));

  MTHD_VIRTUAL(void onCursorPointerEnter());

  MTHD_VIRTUAL(void onCursorPointerLeave());

  MTHD_VIRTUAL(void onMouseClick());

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
