#ifndef SWAY_UI_ORIENTABLE_HPP
#define SWAY_UI_ORIENTABLE_HPP

#include <sway/core.hpp>
#include <sway/ui/orientations.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

class Orientable {
public:
  Orientable(Orientation orien)
      : orientation_(orien) {}

  ~Orientable() = default;

  [[nodiscard]]
  auto getOrientation() const -> Orientation {
    return orientation_;
  }

private:
  Orientation orientation_;
};

NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_ORIENTABLE_HPP
