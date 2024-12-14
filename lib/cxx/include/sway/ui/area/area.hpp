#ifndef SWAY_UI_AREA_HPP
#define SWAY_UI_AREA_HPP

#include <sway/core.hpp>
#include <sway/ui/area/_typedefs.hpp>
#include <sway/ui/area/areatypes.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class Area {
public:
#pragma region "Ctors/Dtor"

  DTOR_VIRTUAL_DEFAULT(Area);

#pragma endregion

#pragma region "Pure virtual methods"

  PURE_VIRTUAL(auto getType() const -> AreaType);

#pragma endregion
};

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_AREA_HPP
