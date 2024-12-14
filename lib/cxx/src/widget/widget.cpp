#include <sway/ui/area/area.hpp>
#include <sway/ui/area/areatypes.hpp>
#include <sway/ui/area/specs/boxarea.hpp>
#include <sway/ui/area/specs/contentarea.hpp>
#include <sway/ui/builder.hpp>
#include <sway/ui/widget/widget.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

Widget::Widget(BuilderTypedefs::Ptr_t builder)
    : builder_(builder)
    , eventFilter_(nullptr)
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

void Widget::repaint(PainterTypedefs::SharedPtr_t painter) {
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

// void Widget::setMargin(f32_t mrg) {
//   this->getAreaHolder().setEdge<AreaType::IDX_MRG, math::RectEdge::IDX_L>(mrg);
//   this->getAreaHolder().setEdge<AreaType::IDX_MRG, math::RectEdge::IDX_R>(mrg);
//   this->getAreaHolder().setEdge<AreaType::IDX_MRG, math::RectEdge::IDX_T>(mrg);
//   this->getAreaHolder().setEdge<AreaType::IDX_MRG, math::RectEdge::IDX_B>(mrg);
// }

// auto Widget::getMargin() const -> BoxAreaTypedefs::SharedPtr_t {
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
    } else if (childRect.contains(pnt) && child->getMouseFilter() != ois::MouseFilter::Enum::IGNORE) {
      return child.get();
    }
  }

  return nullptr;
}

void Widget::setEventFilter(core::evts::EventHandler::Ptr_t hdl) { eventFilter_ = hdl; }

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

NS_END()  // namespace ui
NS_END()  // namespace sway
