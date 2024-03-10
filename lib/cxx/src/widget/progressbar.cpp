#include <sway/ui/widget/progressbar.hpp>

#include <algorithm>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

ProgressBar::ProgressBar()
    : current_(0.0F) {}

void ProgressBar::update() {}

void ProgressBar::draw(std::shared_ptr<Painter> painter) {
  auto margin = 0.002F;
  auto barLen = (rect_.getR() - (margin * 2.0F)) * current_;

  painter->drawRect(rect_.getL() + margin, rect_.getT() + margin, barLen, rect_.getB() - (margin * 2.0F), COL4F_BLACK);
  painter->drawRect(rect_.getL(), rect_.getT(), rect_.getR(), rect_.getB(), COL4F_WHITE);
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
