#ifndef SWAY_UI_ORIENTABLE_HPP
#define SWAY_UI_ORIENTABLE_HPP

#include <sway/core.hpp>
#include <sway/ui/orientations.hpp>

namespace sway::ui {

class Orientable {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  Orientable(Orientation orien)
      : orientation_(orien) {}

  ~Orientable() = default;

  /** @} */
#pragma endregion

  [[nodiscard]] auto getOrientation() const -> Orientation { return orientation_; }

private:
  Orientation orientation_;
};

}  // namespace sway::ui

#endif  // SWAY_UI_ORIENTABLE_HPP
