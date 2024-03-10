#ifndef SWAY_UI_WIDGET_PROGRESSBAR_HPP
#define SWAY_UI_WIDGET_PROGRESSBAR_HPP

#include <sway/core.hpp>
#include <sway/ui/widget/widget.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class ProgressBar : public Widget {
public:
  ProgressBar();

  ~ProgressBar() = default;

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void draw(std::shared_ptr<Painter> painter));

  void setProgress(f32_t val);

  void addProgress(f32_t val);

private:
  f32_t current_;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_PROGRESSBAR_HPP
