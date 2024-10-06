#ifndef SWAY_UI_WIDGET_PROGRESSBAR_HPP
#define SWAY_UI_WIDGET_PROGRESSBAR_HPP

#include <sway/core.hpp>
#include <sway/ui/widget/widget.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)
NS_BEGIN(widget)

class ProgressBar : public Widget {
public:
#pragma region "Ctors/Dtor"

  ProgressBar(BuilderPtr_t builder);

  virtual ~ProgressBar() = default;

#pragma endregion

#pragma region "Override Widget methods"

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void repaint(Painter::SharedPtr_t painter));

#pragma endregion

  void setProgress(f32_t val);

  void addProgress(f32_t val);

private:
  f32_t current_;
};

NS_END()  // namespace widget
NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGET_PROGRESSBAR_HPP
