#ifndef SWAY_UI_AREA_HPP
#define SWAY_UI_AREA_HPP

#include <sway/core.hpp>
#include <sway/ui/area/_typedefs.hpp>
#include <sway/ui/area/areatypes.hpp>

namespace sway::ui {

class Area {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  virtual ~Area() = default;

  /** @} */
#pragma endregion

#pragma region "Pure virtual methods"

  PURE_VIRTUAL(auto getType() const -> AreaType);

#pragma endregion
};

}  // namespace sway::ui

#endif  // SWAY_UI_AREA_HPP
