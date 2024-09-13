#include <sway/ui/widget/composites/menuitem.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

MenuItem::MenuItem(BuilderPtr_t builder, const std::string &text)
    : Item(builder) {
  button_ = std::make_shared<Button>(this->builder_, text);
  // button_->subscribe(button_.get(), "MouseClicked", EVENT_HANDLER(MenuScreenView, handlePlayMouseClickedEvent));
  this->addChildNode(button_);
  this->needsRepainting_ = true;
}

void MenuItem::update() {
  // auto x = 1.0F;
  // auto color = (u8_t)std::floor(255.0F * ((x > 1.0F) ? (2.0F - x) : (x)));
  // auto foregroundColor = COL4F_PURPLE | (color << 16);

  Item::update();
}

void MenuItem::repaint(Painter::SharedPtr_t painter) {
  if (this->needsRepainting_) {
    button_->setAlignment(math::Alignment::CENTER);
    const auto offset = this->getOffset().computed;
    button_->setOffset(offset);
    button_->setSize(this->getSize());
    this->needsRepainting_ = false;
  }

  Item::repaint(painter);
}

void MenuItem::updateState() {}

void MenuItem::focusGained() {
  updateState();
  this->needsRepainting_ = true;
}

void MenuItem::focusLost() {
  updateState();
  this->needsRepainting_ = true;
}

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
