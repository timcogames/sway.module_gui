#include <sway/ui/builder.hpp>
#include <sway/ui/controls/button/button.hpp>
#include <sway/ui/zindex.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

auto Button::create(BuilderTypedefs::Ptr_t builder, const std::string &text) -> ButtonTypedefs::SharedPtr_t {
  return std::make_shared<Button>(builder, text);
}

Button::Button(BuilderTypedefs::Ptr_t builder, const std::string &text)
    : Widget(builder)
    , hovering_(false) {
  textView_ = std::make_shared<TextView>(builder, text);
  this->addChildNode(textView_);
}

Button::~Button() { this->removeChildNode(textView_); }

void Button::updateState() {
  const auto oldState = hovering_;
  hovering_ = this->builder_->getWidgetUnderPointer()->getNodeIdx().equal(this->getNodeIdx());
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

void Button::repaint(PainterTypedefs::SharedPtr_t painter) {
  auto zindex = getZIndex(1);
  auto offset = this->getOffset().computed;

  painter->drawRect(math::rect4f_t(offset.getX(), offset.getY(), this->getSize()), this->getBackgroundColor(), zindex);

  Widget::repaint(painter);
}

NS_END()  // namespace ui
NS_END()  // namespace sway
