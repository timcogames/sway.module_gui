#ifndef SWAY_UI_WIDGET_RADIOBUTTONGROUP_HPP
#define SWAY_UI_WIDGET_RADIOBUTTONGROUP_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/linearlayout.hpp>
#include <sway/ui/widget/linearlayoutorientations.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

struct RadioButtonGroupChangeEventData : public core::foundation::EventData {
  core::container::NodeIdx nodeidx;

  // clang-format off
  MTHD_OVERRIDE(auto serialize() const -> std::string) { return ""; }  // clang-format on

  MTHD_OVERRIDE(void deserialize(const std::string &jdata)) {}
};

class RadioButtonGroup : public LinearLayout {
public:
  DECLARE_EVENT(EVT_CHANGED, RadioButtonGroupChanged)

  RadioButtonGroup(Builder *builder, LinearLayoutOrientation orientation);

  virtual ~RadioButtonGroup() = default;

  void deselect();

  void handleAddNode(core::foundation::Event *evt);

  void handleClickedEvent(core::foundation::Event *evt);

private:
  std::optional<std::shared_ptr<RadioButton>> selected_;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_RADIOBUTTONGROUP_HPP
