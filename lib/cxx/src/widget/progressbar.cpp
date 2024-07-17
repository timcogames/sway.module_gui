#include <sway/ui/builder.hpp>
#include <sway/ui/widget/progressbar.hpp>

#include <algorithm>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

ProgressBar::ProgressBar(Builder::Ptr_t builder)
    : Widget(builder)
    , current_(0.0F) {}

void ProgressBar::update() {}

void ProgressBar::paintEvent(Painter::SharedPtr_t painter) {
  auto rectWithMargin = rect_;
  rectWithMargin.reduce(math::Margin<f32_t>(1.5F));

  auto barLen = rectWithMargin.getL() + rectWithMargin.getW() * current_;

  painter->drawRect(rectWithMargin.getL(), rectWithMargin.getT(), barLen, rectWithMargin.getB(), COL4F_BEIGE);
  painter->drawRect(rect_.getL(), rect_.getT(), rect_.getR(), rect_.getB(), COL4F_GRAY1);
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
