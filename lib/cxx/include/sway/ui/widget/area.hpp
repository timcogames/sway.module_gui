#ifndef SWAY_UI_WIDGETS_AREA_HPP
#define SWAY_UI_WIDGETS_AREA_HPP

#include <sway/core.hpp>
#include <sway/ui/widget/areatypes.hpp>
#include <sway/ui/widget/typedefs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

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

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGETS_AREA_HPP
