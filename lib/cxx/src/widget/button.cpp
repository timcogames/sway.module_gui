#include <sway/ui/builder.hpp>
#include <sway/ui/widget/button.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

Button::Button(BuilderPtr_t builder, const std::string &text)
    : Widget(builder)
    , hovering_(false) {
  label_ = std::make_shared<Label>(this->builder_, text);
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

void Button::repaint(Painter::SharedPtr_t painter) {
  auto offset = this->getOffset();

  label_->setAlignment(math::Alignment::CENTER);
  label_->setOffset(offset);
  label_->setSize(this->getSize());

  painter->drawRect(math::rect4f_t(offset.getX(), offset.getY(), this->getSize()), this->getBackgroundColor());

  Widget::repaint(painter);
}

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
