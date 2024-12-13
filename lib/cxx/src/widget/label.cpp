#include <sway/ui/builder.hpp>
#include <sway/ui/widget/label.hpp>
#include <sway/ui/zindex.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

Label::Label(BuilderTypedefs::Ptr_t builder, const std::string &text)
    : Widget(builder)
    , text_(text)
    , font_("")
    , fontSize_(12) {
  setMouseFilter(ois::MouseFilter::Enum::IGNORE);

#ifdef UI_USE_GMOCK
  // TODO
#else
  resize();
#endif
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

void Label::repaint(PainterTypedefs::SharedPtr_t painter) {
  auto zindex = getZIndex(2);
  auto offset = this->getOffset().computed;

  painter->drawText(
      math::rect4f_t(offset.getX(), offset.getY(), this->getSize()), this->getForegroundColor(), text_.c_str(), zindex);
}

void Label::setText(const std::string &text) { text_ = text; }

NS_END()  // namespace ui
NS_END()  // namespace sway
