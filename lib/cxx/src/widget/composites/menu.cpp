#include <sway/core.hpp>
#include <sway/ui/builder.hpp>
#include <sway/ui/layout/specs/linearlayout.hpp>
#include <sway/ui/orientations.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/menu.hpp>
#include <sway/ui/widget/composites/menueventhandler.hpp>
#include <sway/ui/widget/composites/menuitem.hpp>

#include <memory>
#include <string>
#include <unordered_map>

namespace sway::ui {

Menu::Menu(BuilderTypedefs::Ptr_t builder, Orientation orien)
    : Widget(builder) {
  subscriber_ = this->builder_->getEventBus()->subscribe(new MenuEventHandler(this));
}

Menu::~Menu() { this->builder_->getEventBus()->unsubscribe(subscriber_); }

void Menu::addItem(const std::string &text) {
  auto item = std::make_shared<MenuItem>(this->builder_, text);
  item->setAlignment(math::Alignment::CENTER);
  item->setOffset(0.0F, 0.0F);
  item->setSize(150.0F, 70.0F);
  this->addChildNode(item);
}

// void Menu::update() {}

// void Menu::repaint(PainterTypedefs::SharedPtr_t painter) {}

}  // namespace sway::ui
