#ifndef SWAY_UI_WIDGET_PROGRESSBAR_HPP
#define SWAY_UI_WIDGET_PROGRESSBAR_HPP

#include <sway/core.hpp>
#include <sway/ui/widget/progress/progressmodes.hpp>
#include <sway/ui/widget/widget.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)
NS_BEGIN(widget)

class ProgressBar : public Widget {
public:
#pragma region "Ctors/Dtor"

  ProgressBar(BuilderTypedefs::Ptr_t builder);

  DTOR_VIRTUAL_DEFAULT(ProgressBar);

#pragma endregion

#pragma region "Overridden Widget methods"

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void repaint(PainterTypedefs::SharedPtr_t painter));

#pragma endregion

  void setProgress(f32_t val);

  void addProgress(f32_t val);

#pragma region "Getters/Setters"

  [[nodiscard]] auto getMode() const -> ProgressMode::Enum { return mode_; }

  void setMode(ProgressMode::Enum mode) { mode_ = mode; }

#pragma endregion

private:
  ProgressMode::Enum mode_;
  f32_t current_;
  f32_t total_;
};

NS_END()  // namespace widget
NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGET_PROGRESSBAR_HPP
