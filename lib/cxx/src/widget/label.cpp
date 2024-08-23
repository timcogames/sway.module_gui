#include <sway/ui/builder.hpp>
#include <sway/ui/widget/label.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

Label::Label(BuilderPtr_t builder, const std::string &text)
    : Widget(builder)
    , text_(text)
    , font_("")
    , fontSize_(12) {
  setMouseFilter(ois::MouseFilter::IGNORE);

  resize();
}

void Label::resize() {
  auto fnt = builder_->getPainter()->getDefaultFont();
  auto wdt = 0.0F;
  auto hgt = 0.0F;

  for (auto i = 0; i < text_.size(); ++i) {
    auto charInfo = fnt->getCharInfo(text_[i]);
    if (!charInfo.has_value()) {
      return;
    }

    auto charSize = charInfo.value().size;
    auto charOffset = charInfo.value().bitmapGlyphOffset;

    wdt += charOffset.getX() + static_cast<f32_t>(charSize.getW());
    hgt = std::max(hgt, static_cast<f32_t>(charSize.getH()));
  }

  this->setSize(wdt, hgt);
}

void Label::update() {}

void Label::repaint(Painter::SharedPtr_t painter) {
  auto position = this->getPosition();
  painter->drawText(
      math::rect4f_t(position.getX(), position.getY(), this->getSize()), this->getForegroundColor(), text_.c_str());
}

void Label::setText(const std::string &text) { text_ = text; }

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
