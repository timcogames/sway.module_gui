#ifndef SWAY_UI_WIDGET_WIDGET_HPP
#define SWAY_UI_WIDGET_WIDGET_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/appearance.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class Widget : public core::container::Node {
public:
  Widget();

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

  auto getChildAt(const math::point2f_t &point) -> Widget * {
    for (auto node : this->getChildNodes()) {
      auto child = std::static_pointer_cast<Widget>(node);
      if (!child->hasVisible()) {
        break;
      }

      std::cout << child->getRect() << std::endl;

      if (auto *const widget = child->getChildAt(point)) {
        return widget;
      } else if (child->getRect().contains(point)) {
        child->setHover(true);
        return child.get();
      }

      child->setHover(false);
    }

    return nullptr;
  }

  void setHover(bool val) { hovered_ = val; }

  auto hasHovered() -> bool { return hovered_; }

protected:
  math::rect4f_t rect_;

  Appearance appearance_;

  bool visibled_;
  bool hovered_;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_WIDGET_HPP
