#include <sway/ui/area/area.hpp>
#include <sway/ui/area/areatypes.hpp>
#include <sway/ui/area/specs/boxarea.hpp>
#include <sway/ui/area/specs/contentarea.hpp>
#include <sway/ui/builder.hpp>
#include <sway/ui/widget/widget.hpp>

namespace sway::ui {

Widget::Widget(BuilderPtr_t builder)
    : builder_(builder)
    , needsRepainting_(false) {
  setBackgroundColor(COL4F_GRAY1);
  setForegroundColor(COL4F_BEIGE);
}

void Widget::update() {
  for (auto const &child : this->getChildNodes()) {
    std::static_pointer_cast<Widget>(child)->update();
  }
}

void Widget::repaint(PainterSharedPtr_t painter) {
  if (!this->isVisible()) {
    return;
  }

  for (auto const &child : this->getChildNodes()) {
    auto widget = core::NodeUtil::cast<Widget>(child);
    if (widget->getBarrierType() != BarrierType::LAYOUT) {
      widget->repaint(painter);
    } else {
      for (auto const &child2 : widget->getChildNodes()) {
        auto widget2 = core::NodeUtil::cast<Widget>(child2);
        if (widget2->getBarrierType() != BarrierType::LAYOUT) {
          widget2->repaint(painter);
        }
      }
    }
  }
}

// void Widget::setMargin(f32_t mrg) {
//   this->getAreaHolder().setEdge<AreaType::IDX_MRG, math::RectEdge::IDX_L>(mrg);
//   this->getAreaHolder().setEdge<AreaType::IDX_MRG, math::RectEdge::IDX_R>(mrg);
//   this->getAreaHolder().setEdge<AreaType::IDX_MRG, math::RectEdge::IDX_T>(mrg);
//   this->getAreaHolder().setEdge<AreaType::IDX_MRG, math::RectEdge::IDX_B>(mrg);
// }

// auto Widget::getMargin() const -> BoxAreaSharedPtr_t {
//   return this->areaHolder_.getArea<AreaType::IDX_MRG>().value();
// }

void Widget::setBackgroundColor(const math::col4f_t &col) {
  appearance_.background[core::toBase(WidgetColorGroup::INACTIVE)][core::toBase(WidgetColorState::NORM)] = col;
}

auto Widget::getBackgroundColor() const -> math::col4f_t {
  return appearance_.background[core::toBase(WidgetColorGroup::INACTIVE)][core::toBase(WidgetColorState::NORM)];
}

void Widget::setForegroundColor(const math::col4f_t &col) {
  appearance_.text[core::toBase(WidgetColorGroup::INACTIVE)][core::toBase(WidgetColorState::NORM)] = col;
}

auto Widget::getForegroundColor() const -> math::col4f_t {
  return appearance_.text[core::toBase(WidgetColorGroup::INACTIVE)][core::toBase(WidgetColorState::NORM)];
}

// void Widget::setEventFilter(core::evts::EventHandlerTypedefs::Ptr_t hdl) { eventFilter_ = hdl; }

void Widget::setAlignment(math::Alignment alignment) { alignment_ = alignment; }

// void Widget::setHover(bool val) {
//   // if (hovered_ == val) {
//   //   return;
//   // }

//   // hovered_ = val;

//   // auto *eventdata = new WidgetEventData();
//   // eventdata->uid = this->getNodeIndex().toStr();
//   // // clang-format off
//   // auto event = std::make_unique<WidgetEvent>(core::toBase(hovered_
//   //     ? WidgetEventType::POINTER_ENTER
//   //     : WidgetEventType::POINTER_LEAVE), eventdata);
//   // // clang-format on
//   // this->builder_->getEventBus()->addToQueue(std::move(event));
// }

}  // namespace sway::ui
