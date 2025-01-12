#ifndef SWAY_UI_RADIOBUTTONGROUP_HPP
#define SWAY_UI_RADIOBUTTONGROUP_HPP

#include <sway/core.hpp>
#include <sway/ui/layout/specs/linearlayout.hpp>
#include <sway/ui/orientations.hpp>
#include <sway/ui/painter.hpp>

#include <memory>
#include <string>

namespace sway::ui {

class RadioButtonGroup : public LinearLayout {
  DECLARE_EVENT(EVT_CHANGED, RadioButtonGroupChanged)

public:
  using Ptr_t = RadioButtonGroup *;
  using SharedPtr_t = std::shared_ptr<RadioButtonGroup>;

#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  RadioButtonGroup(BuilderTypedefs::Ptr_t builder, Orientation orientation);

  virtual ~RadioButtonGroup() = default;

  /** @} */
#pragma endregion

  void deselect();

  auto handleAddNode(const core::EventTypedefs::UniquePtr_t &evt) -> bool;

  auto handleClickedEvent(const core::EventTypedefs::UniquePtr_t &evt) -> bool;

private:
  RadioButtonTypedefs::OptionalSharedPtr_t selected_;
};

}  // namespace sway::ui

#endif  // SWAY_UI_RADIOBUTTONGROUP_HPP
