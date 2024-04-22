#include <sway/ui/builder.hpp>
#include <sway/ui/widget/label.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

Label::Label(Builder *builder, const std::string &text)
    : Widget(builder)
    , text_(text)
    , font_("")
    , fontSize_(12) {
  setMouseFilter(ois::MouseFilter::IGNORE);
}

void Label::update() {}

void Label::paintEvent(std::shared_ptr<Painter> painter) {
  painter->drawText(rect_.getL(), rect_.getT(), rect_.getR(), rect_.getB(), this->getForegroundColor(), text_.c_str());
}

void Label::setText(const std::string &text) { text_ = text; }

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
