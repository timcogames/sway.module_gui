#include <sway/ui/builder.hpp>
#include <sway/ui/widget/area.hpp>
#include <sway/ui/widget/areas/boxarea.hpp>
#include <sway/ui/widget/areas/contentarea.hpp>
#include <sway/ui/widget/areatypes.hpp>
#include <sway/ui/widget/widget.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

Widget::Widget(BuilderPtr_t builder)
    : builder_(builder)
    , eventFilter_(nullptr)
    , mouseFilter_(ois::MouseFilter::STOP)
    , containsPointer_(false)
    , needsRepainting_(false) {
  setBackgroundColor(COL4F_GRAY1);
  setForegroundColor(COL4F_BEIGE);
}

void Widget::update() {
  for (auto const &child : this->getChildNodes()) {
    std::static_pointer_cast<Widget>(child)->update();
  }
}

void Widget::repaint(Painter::SharedPtr_t painter) {
  if (!this->isVisible()) {
    return;
  }

  for (auto const &child : this->getChildNodes()) {
    std::static_pointer_cast<Widget>(child)->repaint(painter);
  }
}

void Widget::onCursorPointerEnter() {
  containsPointer_ = true;
  this->update();

  auto *evtdata = new PointerEnterEventData();
  auto *evt = new PointerEnterEvent(0, evtdata);

  emit(EVT_POINTER_ENTER, evt, [&](core::foundation::EventHandler::Ptr_t) { return true; });
}

void Widget::onCursorPointerLeave() {
  containsPointer_ = false;
  this->update();

  auto *evtdata = new PointerLeaveEventData();
  auto *evt = new PointerLeaveEvent(0, evtdata);

  emit(EVT_POINTER_LEAVE, evt, [&](core::foundation::EventHandler::Ptr_t) { return true; });
}

void Widget::onMouseClick(u32_t state) {
  this->update();

  if (eventFilter_ != nullptr) {
    //   eventFilter_->handle(this, event);
  }

  auto *evtdata = new MouseClickEventData();
  evtdata->nodeidx = this->getNodeIdx();
  evtdata->state = state;
  auto *evt = new MouseClickedEvent(0, std::move(evtdata));

  emit(EVT_MOUSE_CLICKED, evt, [&](core::foundation::EventHandler::Ptr_t) { return true; });
}

auto Widget::hasRelated() -> bool {
  auto parentOpt = this->getParentNode();
  if (!parentOpt.has_value()) {
    return false;
  }

  auto parent = parentOpt.value();
  return (parent->getNodeIdx().chainEqual(std::vector<i32_t>({-1}))) ? false : true;
}

void Widget::setSize(const math::size2f_t &size) {
  this->getAreaHolder().getArea<AreaType::IDX_CNT>().value()->setSize(size);
}

void Widget::setSize(f32_t wdt, f32_t hgt) { setSize(math::size2f_t(wdt, hgt)); }

auto Widget::getSize() const -> math::size2f_t {
  return this->getAreaHolder().getArea<AreaType::IDX_CNT>().value()->getSize();
}

// void Widget::setMargin(f32_t mrg) {
//   this->getAreaHolder().setEdge<AreaType::IDX_MRG, math::RectEdge::IDX_L>(mrg);
//   this->getAreaHolder().setEdge<AreaType::IDX_MRG, math::RectEdge::IDX_R>(mrg);
//   this->getAreaHolder().setEdge<AreaType::IDX_MRG, math::RectEdge::IDX_T>(mrg);
//   this->getAreaHolder().setEdge<AreaType::IDX_MRG, math::RectEdge::IDX_B>(mrg);
// }

// auto Widget::getMargin() const -> BoxArea::SharedPtr_t {
//   return this->areaHolder_.getArea<AreaType::IDX_MRG>().value();
// }

void Widget::setBackgroundColor(const math::col4f_t &col) {
  appearance_
      .background[core::detail::toBase(WidgetColorGroup::INACTIVE)][core::detail::toBase(WidgetColorState::NORM)] = col;
}

auto Widget::getBackgroundColor() const -> math::col4f_t {
  return appearance_
      .background[core::detail::toBase(WidgetColorGroup::INACTIVE)][core::detail::toBase(WidgetColorState::NORM)];
}

void Widget::setForegroundColor(const math::col4f_t &col) {
  appearance_.text[core::detail::toBase(WidgetColorGroup::INACTIVE)][core::detail::toBase(WidgetColorState::NORM)] =
      col;
}

auto Widget::getForegroundColor() const -> math::col4f_t {
  return appearance_
      .text[core::detail::toBase(WidgetColorGroup::INACTIVE)][core::detail::toBase(WidgetColorState::NORM)];
}

auto Widget::getChildAtPoint(const math::point2f_t &pnt) -> Widget::Ptr_t {
  for (auto node : this->getChildNodes()) {
    auto child = std::static_pointer_cast<Widget>(node);
    if (!child->isVisible()) {
      break;
    }

    const auto childPos = child->getOffset().computed;
    auto childRect = math::rect4f_t(childPos.getX(), childPos.getY(), child->getOuterSize());

    // std::cout << childRect << " / " << pnt << std::endl;

    if (auto *const widget = child->getChildAtPoint(pnt)) {
      return widget;
    } else if (childRect.contains(pnt) && child->getMouseFilter() != ois::MouseFilter::IGNORE) {
      return child.get();
    }
  }

  return nullptr;
}

void Widget::setEventFilter(core::evts::EventHandler::Ptr_t hdl) { eventFilter_ = hdl; }

void Widget::setMouseFilter(ois::MouseFilter filter) { mouseFilter_ = filter; }

auto Widget::getMouseFilter() const -> ois::MouseFilter { return mouseFilter_; }

void Widget::setAlignment(math::Alignment alignment) { alignment_ = alignment; }

// void Widget::setHover(bool val) {
//   // if (hovered_ == val) {
//   //   return;
//   // }

//   // hovered_ = val;

//   // auto *eventdata = new WidgetEventData();
//   // eventdata->uid = this->getNodeIdx().toStr();
//   // // clang-format off
//   // auto event = std::make_unique<WidgetEvent>(core::detail::toBase(hovered_
//   //     ? WidgetEventType::POINTER_ENTER
//   //     : WidgetEventType::POINTER_LEAVE), eventdata);
//   // // clang-format on
//   // this->builder_->getEventBus()->addToQueue(std::move(event));
// }

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
