#include <sway/ois/events/inputevent.hpp>
#include <sway/ois/events/keyeventhandler.hpp>
#include <sway/ois/events/mouseevent.hpp>
#include <sway/ois/web/emsmouse.hpp>
#include <sway/ui/builder.hpp>

namespace sway::ui {

struct WidgetEventHandler : public core::EventHandler {
  WidgetEventHandler(BuilderPtr_t builder)
      : core::EventHandler(nullptr)
      , builder_(builder) {}

  ~WidgetEventHandler() override = default;

  MTHD_OVERRIDE(auto invoke(core::EventTypedefs::UniquePtr_t &&evt) -> bool) final {
    if (ois::InputEventUtil::isMouseEvent(evt)) {
      auto mouseEvtData = evt->getConcreteData<ois::MouseEventData>();
      if (evt->getType() == core::toBase(ois::InputActionType::MOUSE_MOVED)) {
        builder_->setCursorPoint(mouseEvtData.point);
      }

      auto cursor = builder_->getCursor();
      auto target = builder_->getRootWidget()->getChildAtPoint(cursor.pnt);

      builder_->updateWidgetUnderPointer(target);

      if (evt->getType() == core::toBase(ois::InputActionType::MOUSE_BUTTON)) {
        if (mouseEvtData.btnCode == core::toBase(ois::MouseButtonCode::LMB)) {
          builder_->handleMouseClick(mouseEvtData.state);
        }
      }
    }

    return true;
  }

private:
  BuilderPtr_t builder_;
};

Builder::Builder(core::typedefs::ContextPtr_t context)
    : core::Object(context)
    , currWidgetUnderPointer_(nullptr)
    , painter_(nullptr) {}

void Builder::initialize() {
  root_ = std::make_shared<Widget>(this);
  subscriber_ = evtbus_->subscribe(new WidgetEventHandler(this));

  // root_->setAbsolutePosition(0, 0);
  // root_->setSize(800, 600);
}

void Builder::deinit() {
  evtbus_->unsubscribe(subscriber_);
  currWidgetUnderPointer_ = nullptr;
}

void Builder::update() { root_->repaint(painter_); }

void Builder::updateWidgetUnderPointer(ElementUnderPointer_t target) {
  if (currWidgetUnderPointer_ == target) {
    return;
  }

  auto prevWidgetUnderPointer = currWidgetUnderPointer_;
  currWidgetUnderPointer_ = target;

  if (prevWidgetUnderPointer) {
    prevWidgetUnderPointer->onCursorPointerLeave();
  }

  if (currWidgetUnderPointer_) {
    currWidgetUnderPointer_->onCursorPointerEnter();
  }
}

void Builder::handleMouseClick(u32_t state) {
  if (currWidgetUnderPointer_) {
    currWidgetUnderPointer_->onMouseClick(state);
  }
}

}  // namespace sway::ui
