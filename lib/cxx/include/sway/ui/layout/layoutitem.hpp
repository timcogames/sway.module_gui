#ifndef SWAY_UI_LAYOUTITEM_HPP
#define SWAY_UI_LAYOUTITEM_HPP

#include <sway/render/updatable.hpp>
#include <sway/ui/_stdafx.hpp>
#include <sway/ui/element/_typedefs.hpp>
#include <sway/ui/element/element.hpp>
#include <sway/ui/layout/_typedefs.hpp>

namespace sway::ui {

class LayoutItem : public Element, public render::Updatable {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  LayoutItem();

  virtual ~LayoutItem() = default;

  /** @} */
#pragma endregion

#pragma region "Overridden Updatable methods"

  virtual void update() {}

#pragma endregion

#pragma region "Overridden Element methods"

  void recursiveUpdateItemOffsets(const math::point2f_t offset) override;

#pragma endregion

  MTHD_OVERRIDE(auto getBarrierType() const -> BarrierType) { return BarrierType::NONE; }
};

}  // namespace sway::ui

#endif  // SWAY_UI_LAYOUTITEM_HPP
