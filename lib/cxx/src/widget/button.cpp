#include <sway/ui/widget/button.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

Button::Button(const std::string &text) {
  label_ = std::make_shared<Label>(text);
  this->addChildNode(label_);
}

void Button::update() {
  if (this->hasHovered()) {
    label_->setForegroundColor(COL4F_BLACK);
    this->setBackgroundColor(COL4F_WHITE);
  } else {
    label_->setForegroundColor(COL4F_WHITE);
    this->setBackgroundColor(COL4F_BLUE);
  }
}

void Button::paintEvent(std::shared_ptr<Painter> painter) {
  label_->setPosition(math::vec2f_t(rect_.getL(), rect_.getT()));
  label_->paintEvent(painter);

  painter->drawRect(rect_.getL(), rect_.getT(), rect_.getR(), rect_.getB(), this->getBackgroundColor());
}

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
