#ifndef SWAY_UI_WIDGET_WIDGET_HPP
#define SWAY_UI_WIDGET_WIDGET_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ui/painter.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class Widget : public core::container::Node {
public:
  Widget();

  ~Widget() = default;

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void draw(std::shared_ptr<Painter> painter));

  void setRect(const math::rect4f_t &rect) { rect_ = rect; }

  [[nodiscard]]
  auto hasRelated() -> bool {
    auto parentOpt = this->getParentNode();
    if (!parentOpt.has_value()) {
      return false;
    }

    auto parent = parentOpt.value();
    return (parent->getNodeIdx().chainEqual(std::vector<int>({-1}))) ? false : true;
  }

  auto setPosition(const math::vec2f_t &pos) {
    rect_.setL(pos.getX());
    rect_.setT(pos.getY());

    if (this->hasRelated()) {
      auto parentOpt = this->getParentNode();
      if (!parentOpt.has_value()) {
        return;
      }

      auto parent = std::static_pointer_cast<Widget>(parentOpt.value());
      rect_.offset(parent->getPosition());
    }
  }

  [[nodiscard]]
  auto getPosition() const -> math::point2f_t {
    return rect_.position();
  }

  auto setSize(const math::size2f_t &size) {
    rect_.setR(rect_.getL() + size.getW());
    rect_.setB(rect_.getT() + size.getH());
  }

protected:
  math::rect4f_t rect_;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_WIDGET_HPP
