#ifndef SWAY_UI_WIDGET_MENUITEM_HPP
#define SWAY_UI_WIDGET_MENUITEM_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/button.hpp>

#include <memory>
#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class Item : public Widget {
public:
  Item(Builder *builder)
      : Widget(builder) {}

  virtual ~Item() = default;

  void select() {}

  void deselect() {}

  void toggle() {}
};

class MenuItem : public Item {
public:
  using Ptr_t = MenuItem *;
  using SharedPtr_t = std::shared_ptr<MenuItem>;

#pragma region "Ctors/Dtor"

  MenuItem(Builder *builder, const std::string &text)
      : Item(builder) {
    button_ = std::make_shared<Button>(this->builder_, text);
    // button_->subscribe(button_.get(), "MouseClicked", EVENT_HANDLER(MenuScreenView, handlePlayMouseClickedEvent));
    this->addChildNode(button_);
    this->needsRepainting_ = true;
  }

  virtual ~MenuItem() = default;

#pragma endregion

#pragma region "Override Widget methods"

  MTHD_OVERRIDE(void update()) {
    // auto x = 1.0F;
    // auto color = (u8_t)std::floor(255.0F * ((x > 1.0F) ? (2.0F - x) : (x)));
    // auto foregroundColor = COL4F_PURPLE | (color << 16);

    Item::update();
  }

  MTHD_OVERRIDE(void repaint(Painter::SharedPtr_t painter)) {
    if (this->needsRepainting_) {
      button_->setAlignment(math::Alignment::CENTER);
      button_->setPosition(math::vec2f_t(this->rect_.getL(), this->rect_.getT()));
      button_->setSize(this->rect_.asSize());
      this->needsRepainting_ = false;
    }

    Item::repaint(painter);
  }

#pragma endregion

  void updateState() {}

  void focusGained() {
    updateState();
    this->needsRepainting_ = true;
  }

  void focusLost() {
    updateState();
    this->needsRepainting_ = true;
  }

private:
  Button::SharedPtr_t button_;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_MENUITEM_HPP
