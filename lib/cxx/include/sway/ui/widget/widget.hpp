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

  auto setPosition(const math::vec2f_t &position) {
    rect_.setL(position.getX());
    rect_.setT(position.getY());
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
