#include <sway/ui/widget/progressbar.hpp>

#include <algorithm>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

ProgressBar::ProgressBar()
    : steps_(0.0F) {}

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
