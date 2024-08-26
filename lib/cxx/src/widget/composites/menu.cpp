#include <sway/core.hpp>
#include <sway/ui/builder.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/menu.hpp>
#include <sway/ui/widget/composites/menueventhandler.hpp>
#include <sway/ui/widget/composites/menuitem.hpp>
#include <sway/ui/widget/layoutorientations.hpp>
#include <sway/ui/widget/linearlayout.hpp>

#include <memory>
#include <string>
#include <unordered_map>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

Menu::Menu(Builder *builder, LayoutOrientation orien)
    : LinearLayout(builder, orien) {
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

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
