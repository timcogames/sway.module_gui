#ifndef SWAY_UI_WIDGET_RADIOBUTTONGROUP_HPP
#define SWAY_UI_WIDGET_RADIOBUTTONGROUP_HPP

#include <sway/core.hpp>
#include <sway/ui/orientations.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/linearlayout.hpp>

#include <memory>
#include <string>

NS_BEGIN_SWAY()
NS_BEGIN(ui)
NS_BEGIN(widget)

struct RadioButtonGroupChangeEventData : public core::foundation::EventData {
  core::container::NodeIdx nodeidx;

  MTHD_OVERRIDE(auto serialize() const -> std::string) { return ""; }

  MTHD_OVERRIDE(void deserialize(const std::string &jdata)) {}
};

class RadioButtonGroup : public LinearLayout {
  DECLARE_EVENT(EVT_CHANGED, RadioButtonGroupChanged)

public:
  using Ptr_t = RadioButtonGroup *;
  using SharedPtr_t = std::shared_ptr<RadioButtonGroup>;

#pragma region "Ctors/Dtor"

  RadioButtonGroup(BuilderTypedefs::Ptr_t builder, Orientation orientation);

  DTOR_VIRTUAL_DEFAULT(RadioButtonGroup);

#pragma endregion

  void deselect();

  void handleAddNode(core::foundation::EventPtr_t evt);

  void handleClickedEvent(core::foundation::EventPtr_t evt);

private:
  std::optional<RadioButton::SharedPtr_t> selected_;
};

NS_END()  // namespace widget
NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGET_RADIOBUTTONGROUP_HPP
