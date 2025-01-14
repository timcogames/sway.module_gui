#ifndef SWAY_UI_RADIOBUTTONGROUP_HPP
#define SWAY_UI_RADIOBUTTONGROUP_HPP

#include <sway/ui/_stdafx.hpp>
#include <sway/ui/layout/specs/linearlayout.hpp>
#include <sway/ui/orientations.hpp>
#include <sway/ui/painter.hpp>

namespace sway::ui {

class RadioButtonGroup : public LinearLayout {
  DECLARE_EVENT(EVT_CHANGED, RadioButtonGroupChanged)

public:
#pragma region "Pointer aliases"
  /** \~english @name Pointer aliases */ /** \~russian @name Типы указателей */
  /** @{ */

  using Ptr_t = RadioButtonGroupPtr_t;
  using SharedPtr_t = RadioButtonGroupSharedPtr_t;

  /** @} */
#pragma endregion

#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  RadioButtonGroup(BuilderPtr_t builder, Orientation orientation);

  virtual ~RadioButtonGroup() = default;

  /** @} */
#pragma endregion

  void deselect();

  auto handleAddNode(const core::EventTypedefs::UniquePtr_t &evt) -> bool;

  auto handleClickedEvent(const core::EventTypedefs::UniquePtr_t &evt) -> bool;

private:
  RadioButtonOptionalSharedPtr_t selected_;
};

}  // namespace sway::ui

#endif  // SWAY_UI_RADIOBUTTONGROUP_HPP
