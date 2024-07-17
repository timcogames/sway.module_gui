#include <sway/ui/builder.hpp>
#include <sway/ui/widget/button.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

Button::Button(Builder::Ptr_t builder, const std::string &text)
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
    label_->setForegroundColor(COL4F_WHITE);
    this->setBackgroundColor(COL4F_GRAY2);
  } else {
    label_->setForegroundColor(COL4F_BEIGE);
    this->setBackgroundColor(COL4F_GRAY1);
  }
}

void Button::paintEvent(Painter::SharedPtr_t painter) {
  label_->setAlignment(math::Alignment::CENTER);
  label_->setPosition(math::vec2f_t(rect_.getL(), rect_.getT()));
  label_->setSize(rect_.asSize());

  painter->drawRect(rect_.getL(), rect_.getT(), rect_.getR(), rect_.getB(), this->getBackgroundColor());

  Widget::paintEvent(painter);
}

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
