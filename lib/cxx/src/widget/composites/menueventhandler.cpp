#include <sway/core.hpp>
#include <sway/ois/web/emskeyboard.hpp>
#include <sway/ui/widget/composites/menu.hpp>
#include <sway/ui/widget/composites/menueventhandler.hpp>
#include <sway/ui/widget/composites/menuitem.hpp>

#include <memory>

namespace sway::ui {

MenuEventHandler::MenuEventHandler(Menu *menu)
    : core::EventHandler(nullptr)
    , menu_(menu) {
  scheme_ = MenuControlScheme::reset(/*menu_->getOrientation()*/ Orientation::HORZ);
}

auto MenuEventHandler::invoke(core::EventTypedefs::UniquePtr_t &&evt) -> bool {
  if (ois::InputEventUtil::isKeyEvent(evt)) {
    onKeyEvent(ois::InputEventUtil::asKeyEvent(evt));
  }

  return true;
}

void MenuEventHandler::onKeyEvent(ois::typedefs::KeyEventPtr_t evt) {
  auto evtData = evt->getConcreteData<ois::KeyEventData>();

  if (evtData.state == core::toBase(ois::InputActionState::PRESSED)) {
    if (scheme_.prevItem.button->equal(evtData.keyCode)) {
      std::cout << scheme_.prevItem.description.c_str() << std::endl;
    }

    if (scheme_.nextItem.button->equal(evtData.keyCode)) {
      std::cout << scheme_.nextItem.description.c_str() << std::endl;
    }

    if (scheme_.enter.button->equal(evtData.keyCode)) {
      std::cout << scheme_.enter.description.c_str() << std::endl;
    }
  }
}

}  // namespace sway::ui
