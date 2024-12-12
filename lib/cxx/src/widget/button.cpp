#include <sway/ui/builder.hpp>
#include <sway/ui/widget/button.hpp>
#include <sway/ui/zindex.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)
NS_BEGIN(widget)

Button::Button(BuilderTypedefs::Ptr_t builder, const std::string &text)
    : Widget(builder)
    , hovering_(false) {
  labelWidget_ = std::make_shared<Label>(builder, text);
  this->addChildNode(labelWidget_);
}

Button::~Button() { this->removeChildNode(labelWidget_); }

void Button::update() {
  const auto oldState = hovering_;
  hovering_ = this->builder_->getWidgetUnderPointer()->getNodeIdx().equal(this->getNodeIdx());
  if (oldState == hovering_) {
    return;
  }

  if (hovering_) {
    labelWidget_->setForegroundColor(COL4F_WHITE);
    this->setBackgroundColor(COL4F_GRAY2);
  } else {
    labelWidget_->setForegroundColor(COL4F_BEIGE);
    this->setBackgroundColor(COL4F_GRAY1);
  }
}

void Button::repaint(PainterTypedefs::SharedPtr_t painter) {
  auto zindex = getZIndex(1);
  auto offset = this->getOffset().computed;

  labelWidget_->setAlignment(math::Alignment::CENTER);
  labelWidget_->setOffset(offset);
  labelWidget_->setSize(this->getSize());

  painter->drawRect(math::rect4f_t(offset.getX(), offset.getY(), this->getSize()), this->getBackgroundColor(), zindex);

  Widget::repaint(painter);
}

NS_END()  // namespace widget
NS_END()  // namespace ui
NS_END()  // namespace sway
