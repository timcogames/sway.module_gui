#include <sway/ui/builder.hpp>
#include <sway/ui/widget/button.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

Button::Button(Builder *builder, const std::string &text)
    : Widget(builder)
    , hovering_(false) {
  label_ = std::make_shared<Label>(builder, text);
  this->addChildNode(label_);
}

void Button::update() {
  const auto oldState = hovering_;
  hovering_ = this->builder_->getWidgetUnderPointer()->getNodeIdx().equal(this->getNodeIdx());
  if (oldState == hovering_) {
    return;
  }

  if (hovering_) {
    label_->setForegroundColor(COL4F_BLACK);
    this->setBackgroundColor(COL4F_WHITE);
  } else {
    label_->setForegroundColor(COL4F_WHITE);
    this->setBackgroundColor(COL4F_BLUE);
  }
}

void Button::paintEvent(std::shared_ptr<Painter> painter) {
  label_->setPosition(math::vec2f_t(rect_.getL(), rect_.getB()));
  label_->paintEvent(painter);

  painter->drawRect(rect_.getL(), rect_.getB(), rect_.getR(), rect_.getT(), this->getBackgroundColor());
}

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
