#include <sway/ui/widget/progressbar.hpp>

#include <algorithm>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

ProgressBar::ProgressBar()
    : steps_(0.0F) {}

void ProgressBar::update() {}

void ProgressBar::draw(std::shared_ptr<Painter> painter) {
  painter->drawRect(rect_.getL(), rect_.getT(), rect_.getR(), rect_.getB(), COL4F_WHITE);
}

void ProgressBar::setProgress(f32_t progress) {
  if (steps_ != progress) {
    auto minValue = 0.0F;
    auto maxValue = 1.0F;

    steps_ = std::clamp(progress, minValue, maxValue);
    steps_ = progress;
  }
}

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
