#ifndef SWAY_UI_WIDGET_TOGGLEBUTTON_HPP
#define SWAY_UI_WIDGET_TOGGLEBUTTON_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/button.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class ToggleButton : public Button {
public:
  ToggleButton(Builder *builder, const std::string &text);

  virtual ~ToggleButton() = default;

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void paintEvent(std::shared_ptr<Painter> painter));

  [[nodiscard]]
  auto isChecked() const -> bool {
    return checked_;
  }

  void setChecked(bool val) { checked_ = val; }

private:
  bool checked_;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_TOGGLEBUTTON_HPP
