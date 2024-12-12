#ifndef SWAY_UI_ORIENTABLE_HPP
#define SWAY_UI_ORIENTABLE_HPP

#include <sway/core.hpp>
#include <sway/ui/orientations.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class Orientable {
public:
#pragma region "Ctors/Dtor"

  Orientable(Orientation orien)
      : orientation_(orien) {}

  DTOR_DEFAULT(Orientable);

#pragma endregion

  [[nodiscard]] auto getOrientation() const -> Orientation { return orientation_; }

private:
  Orientation orientation_;
};

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_ORIENTABLE_HPP
