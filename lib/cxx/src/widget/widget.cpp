#include <sway/ui/builder.hpp>
#include <sway/ui/widget/widget.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

Widget::Widget(Builder *builder)
    : builder_(builder)
    , rect_(math::rect4f_t(0.0F, 0.0F, 0.0F, 0.0F))
    , containsPointer_(false)
    , hovered_(false) {
  setBackgroundColor(COL4F_WHITE);
  setForegroundColor(COL4F_BLACK);
}

void Widget::onCursorPointerEnter() {
  containsPointer_ = true;

  auto *evtData = new PointerEnterEventData();
  auto *evt = new PointerEnterEvent(0, evtData);

  emit(EVT_POINTER_ENTER, evt, [&](core::foundation::EventHandler *) { return true; });
}

void Widget::onCursorPointerLeave() {
  containsPointer_ = false;

  auto *evtData = new PointerLeaveEventData();
  auto *evt = new PointerLeaveEvent(0, evtData);

  emit(EVT_POINTER_LEAVE, evt, [&](core::foundation::EventHandler *) { return true; });
}

void Widget::onMouseClick() {
  auto *evtData = new MouseClickEventData();
  auto *evt = new MouseClickedEvent(0, evtData);

  emit(EVT_MOUSE_CLICKED, evt, [&](core::foundation::EventHandler *) { return true; });
}

void Widget::update() {
  for (auto const &child : this->getChildNodes()) {
    std::static_pointer_cast<Widget>(child)->update();
  }
}

void Widget::paintEvent(std::shared_ptr<Painter> painter) {
  if (!this->isVisible()) {
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
  rect_.setB(pos.getY());

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
  rect_.setT(rect_.getB() + size.getH());
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

auto Widget::getChildAtPoint(const math::point2f_t &point) -> Widget * {
  for (auto node : this->getChildNodes()) {
    auto child = std::static_pointer_cast<Widget>(node);
    if (!child->isVisible()) {
      break;
    }

    if (auto *const widget = child->getChildAtPoint(point)) {
      return widget;
    } else if (child->getRect().contains(point)) {
      return child.get();
    }
  }

  return nullptr;
}

void Widget::setHover(bool val) {
  // if (hovered_ == val) {
  //   return;
  // }

  // hovered_ = val;

  // auto *eventdata = new WidgetEventData();
  // eventdata->uid = this->getNodeIdx().toStr();
  // // clang-format off
  // auto event = std::make_unique<WidgetEvent>(core::detail::toUnderlying(hovered_
  //     ? WidgetEventType::POINTER_ENTER
  //     : WidgetEventType::POINTER_LEAVE), eventdata);
  // // clang-format on
  // this->builder_->getEventBus()->addToQueue(std::move(event));
}

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
