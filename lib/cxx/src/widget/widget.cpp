#include <sway/ui/widget/widget.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

Widget::Widget()
    : rect_(math::rect4f_t(0.0F, 0.0F, 0.0F, 0.0F))
    , visibled_(true)
    , hovered_(false) {
  appearance_.background[core::detail::toUnderlying(WidgetColorGroup::INACTIVE)]
                        [core::detail::toUnderlying(WidgetColorState::NORM)] = COL4F_WHITE;

  appearance_.text[core::detail::toUnderlying(WidgetColorGroup::INACTIVE)]
                  [core::detail::toUnderlying(WidgetColorState::NORM)] = COL4F_BLACK;
}

void Widget::update() {
  for (auto const &child : this->getChildNodes()) {
    std::static_pointer_cast<Widget>(child)->update();
  }
}

void Widget::paintEvent(std::shared_ptr<Painter> painter) {
  if (!this->hasVisible()) {
    return;
  }

  for (auto const &child : this->getChildNodes()) {
    std::static_pointer_cast<Widget>(child)->paintEvent(painter);
  }
}

void Widget::setRect(const math::rect4f_t &rect) { rect_ = rect; }

auto Widget::getRect() const -> math::rect4f_t { return rect_; }

auto Widget::hasRelated() -> bool {
  auto parentOpt = this->getParentNode();
  if (!parentOpt.has_value()) {
    return false;
  }

  auto parent = parentOpt.value();
  return (parent->getNodeIdx().chainEqual(std::vector<int>({-1}))) ? false : true;
}

void Widget::setPosition(const math::vec2f_t &pos) {
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

auto Widget::getPosition() const -> math::point2f_t { return rect_.position(); }

void Widget::setSize(const math::size2f_t &size) {
  rect_.setR(rect_.getL() + size.getW());
  rect_.setB(rect_.getT() + size.getH());
}

void Widget::setBackgroundColor(const math::col4f_t &col) {
  appearance_.background[core::detail::toUnderlying(WidgetColorGroup::INACTIVE)]
                        [core::detail::toUnderlying(WidgetColorState::NORM)] = col;
}

auto Widget::getBackgroundColor() const -> math::col4f_t {
  return appearance_.background[core::detail::toUnderlying(WidgetColorGroup::INACTIVE)]
                               [core::detail::toUnderlying(WidgetColorState::NORM)];
}

void Widget::setForegroundColor(const math::col4f_t &col) {
  appearance_.text[core::detail::toUnderlying(WidgetColorGroup::INACTIVE)]
                  [core::detail::toUnderlying(WidgetColorState::NORM)] = col;
}

auto Widget::getForegroundColor() const -> math::col4f_t {
  return appearance_
      .text[core::detail::toUnderlying(WidgetColorGroup::INACTIVE)][core::detail::toUnderlying(WidgetColorState::NORM)];
}

void Widget::setVisible(bool val) { visibled_ = val; }

auto Widget::hasVisible() const -> bool { return visibled_; }

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
