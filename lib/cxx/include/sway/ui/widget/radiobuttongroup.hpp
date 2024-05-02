#ifndef SWAY_UI_WIDGET_RADIOBUTTONGROUP_HPP
#define SWAY_UI_WIDGET_RADIOBUTTONGROUP_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/linearlayout.hpp>
#include <sway/ui/widget/linearlayoutorientations.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class RadioButtonGroup : public LinearLayout {
public:
  RadioButtonGroup(Builder *builder, LinearLayoutOrientation orientation);

  virtual ~RadioButtonGroup() = default;

  void deselect();

private:
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_RADIOBUTTONGROUP_HPP
