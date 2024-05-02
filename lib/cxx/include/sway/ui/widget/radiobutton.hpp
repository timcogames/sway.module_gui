#ifndef SWAY_UI_WIDGET_RADIOBUTTON_HPP
#define SWAY_UI_WIDGET_RADIOBUTTON_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/togglebutton.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class RadioButton : public ToggleButton {
public:
  RadioButton(Builder *builder, const std::string &text);

  virtual ~RadioButton() = default;

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

#endif  // SWAY_UI_WIDGET_RADIOBUTTON_HPP
