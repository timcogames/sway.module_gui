#ifndef SWAY_UI_WIDGETS_AREA_HPP
#define SWAY_UI_WIDGETS_AREA_HPP

#include <sway/core.hpp>
#include <sway/ui/widget/areatypes.hpp>
#include <sway/ui/widget/types.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

class Area {
  DECLARE_CLASS_POINTER_ALIASES(Area)

public:
#pragma region "Ctors/Dtor"

  virtual ~Area() = default;

#pragma endregion

#pragma region "Pure virtual methods"

  PURE_VIRTUAL(auto type() const -> AreaType);

#pragma endregion
};

NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGETS_AREA_HPP
