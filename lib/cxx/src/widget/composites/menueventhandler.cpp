#include <sway/core.hpp>
#include <sway/ois/web/emskeyboard.hpp>
#include <sway/ui/widget/composites/menu.hpp>
#include <sway/ui/widget/composites/menueventhandler.hpp>
#include <sway/ui/widget/composites/menuitem.hpp>

#include <memory>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

MenuEventHandler::MenuEventHandler(Menu *menu)
    : core::evts::EventHandler()
    , menu_(menu) {
  scheme_ = MenuControlScheme::reset(/*menu_->getOrientation()*/ Orientation::HORZ);
}

auto MenuEventHandler::invoke(const core::foundation::Event::UniquePtr_t &evt) -> bool {
  if (ois::InputEventUtil::isKeyEvent(evt)) {
    onKeyEvent(ois::InputEventUtil::asKeyEvent(evt));
  }

  return true;
}

void MenuEventHandler::onKeyEvent(ois::KeyEvent::Ptr_t evt) {
  auto evtData = evt->getConcreteData<ois::KeyEventData>();

  if (evtData.state == core::detail::toBase(ois::InputActionState::PRESSED)) {
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

NS_END()  // namespace ui
NS_END()  // namespace sway
