#include <sway/ui/builder.hpp>
#include <sway/ui/widget/progressbar.hpp>

#include <algorithm>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

ProgressBar::ProgressBar(BuilderPtr_t builder)
    : Widget(builder)
    , current_(0.0F) {}

void ProgressBar::update() {}

void ProgressBar::repaint(Painter::SharedPtr_t painter) {
  const auto offset = this->getOffset();
  auto rectWithMargin = math::rect4f_t(offset.getX(), offset.getY(), this->getSize());
  rectWithMargin.reduce(math::Rect<f32_t>(1.5F, 1.5F, math::size2f_t(1.5F, 1.5F)));

  auto barLen = rectWithMargin.getL() + rectWithMargin.getW() * current_;

  painter->drawRect(rectWithMargin.getL(), rectWithMargin.getT(), barLen, rectWithMargin.getB(), COL4F_BEIGE);
  painter->drawRect(math::rect4f_t(offset.getX(), offset.getY(), this->getSize()), COL4F_GRAY1);
}

void ProgressBar::setProgress(f32_t val) {
  if (current_ == val) {
    return;
  }

  current_ = std::clamp(val, 0.0F, 1.0F);
}

void ProgressBar::addProgress(f32_t val) { this->setProgress(current_ + val); }

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
