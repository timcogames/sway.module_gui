#include <sway/ui/builder.hpp>
#include <sway/ui/controls/button/button.hpp>
#include <sway/ui/zindex.hpp>

namespace sway::ui {

auto Button::create(BuilderPtr_t builder, const std::string &text) -> ButtonTypedefs::SharedPtr_t {
  return std::make_shared<Button>(builder, text);
}

Button::Button(BuilderPtr_t builder, const std::string &text)
    : Widget(builder)
    , hovering_(false) {
  textView_ = std::make_shared<TextView>(builder, text);
  this->addChildNode(textView_);
}

Button::~Button() { this->removeChildNode(textView_); }

void Button::updateState() {
  const auto oldState = hovering_;
  hovering_ = this->builder_->getWidgetUnderPointer()->getNodeIndex().equal(this->getNodeIndex());
  if (oldState == hovering_) {
    return;
  }

  if (hovering_) {
    textView_->setForegroundColor(COL4F_WHITE);
    this->setBackgroundColor(COL4F_GRAY2);
  } else {
    textView_->setForegroundColor(COL4F_BEIGE);
    this->setBackgroundColor(COL4F_GRAY1);
  }
}

void Button::update() {
  textView_->setAlignment(math::Alignment::CENTER);
  textView_->setOffset(this->getOffset().computed);
  // textView_->updateOffset(nullptr);
  textView_->setSize(this->getSize());

  std::cout << "label " << textView_->getOffset().computed << std::endl;

  // updateState();
}

void Button::repaint(PainterSharedPtr_t painter) {
  auto zindex = getZIndex(1);
  auto offset = this->getOffset().computed;

  painter->drawRect(math::rect4f_t(offset.getX(), offset.getY(), this->getSize()), this->getBackgroundColor(), zindex);

  Widget::repaint(painter);
}

}  // namespace sway::ui
