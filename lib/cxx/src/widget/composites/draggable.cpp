#include <sway/core.hpp>
#include <sway/ui/builder.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/draggable.hpp>
#include <sway/ui/zindex.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

Draggable::Draggable(BuilderTypedefs::Ptr_t builder)
    : Widget(builder)
    , hovering_(false)
    , dragging_(false) {
  subscribe(this, "MouseClicked", EVENT_HANDLER(Draggable, handleMouseClickedEvent));
}

Draggable::~Draggable() {}

auto distance(math::point2f_t p1, math::point2f_t p2) -> f32_t {
  return (p1.getX() - p2.getX()) * (p1.getX() - p2.getX()) + (p1.getY() - p2.getY()) * (p1.getY() - p2.getY());
}

void Draggable::handleMouseClickedEvent(core::foundation::Event *evt) {
  auto mouseEvtData = evt->getConcreteData<MouseClickEventData>();
  auto cursor = builder_->getCursor();
  auto offset = this->getOffset();

  if (mouseEvtData.state == core::detail::toBase(ois::InputActionState::PRESSED)) {
    mouseDownPosition_ = cursor.pnt;
    mouseDownOffset_ =
        math::point2f_t(cursor.pnt.getX() - offset.computed.getX(), cursor.pnt.getY() - offset.computed.getY());
    mouseIsDown_ = true;
  } else if (mouseEvtData.state == core::detail::toBase(ois::InputActionState::RELEASED)) {
    mouseIsDown_ = false;
  }
}

void Draggable::update() {
  auto cursor = builder_->getCursor();
  auto parent = std::static_pointer_cast<Element>(this->getParentNode().value());

  if (mouseIsDown_) {
    if (distance(mouseDownPosition_, cursor.pnt) > 2) {
      // mouseDownOffset_.setX(offset.getX());
      // mouseDownOffset_.setY(offset.getY());

      parent->setOffset(
          math::point2f_t(cursor.pnt.getX() - mouseDownOffset_.getX(), cursor.pnt.getY() - mouseDownOffset_.getY()));
      parent->getOffset().markAsDirty();

      parent->updateOffset(nullptr);

      for (const auto &item : parent->getChildNodes()) {
        auto elem = std::static_pointer_cast<Element>(item);
        elem->getOffset().markAsDirty();
        recursiveUpdate(nullptr, elem);
      }
    }
  }
}

void Draggable::repaint(PainterTypedefs::SharedPtr_t painter) {
  update();

  auto offset = this->getOffset().computed;
  painter->drawRect(math::rect4f_t(offset.getX(), offset.getY(), this->getSize()), this->getBackgroundColor(),
      getZIndex((i32_t)core::detail::toBase(ZIndex::DLG_HEAD)));

  Widget::repaint(painter);
}

NS_END()  // namespace ui
NS_END()  // namespace sway
