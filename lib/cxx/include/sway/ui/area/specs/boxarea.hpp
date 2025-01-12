#ifndef SWAY_UI_AREA_BOXAREA_HPP
#define SWAY_UI_AREA_BOXAREA_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ui/area/_typedefs.hpp>
#include <sway/ui/area/area.hpp>
#include <sway/ui/area/areatypes.hpp>

#include <array>
#include <iostream>  // std::ostream
#include <memory>

namespace sway::ui {

class BoxArea : public Area {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  BoxArea(AreaType type);

  virtual ~BoxArea() = default;

  /** @} */
#pragma endregion

#pragma region "Overridden Area methods"

  MTHD_OVERRIDE(auto getType() const -> AreaType);

#pragma endregion

  void resetEdges();

  void set(math::RectEdge::Enum edge, f32_t val);

  void set(f32_t l, f32_t t, f32_t r, f32_t b);

  auto at(math::RectEdge::Enum edge) const -> const f32_t &;

  auto at(math::RectEdge::Enum edge) -> f32_t &;

#pragma region "Getters/Setters"

  [[nodiscard]] auto getL() const -> f32_t;

  [[nodiscard]] auto getT() const -> f32_t;

  [[nodiscard]] auto getR() const -> f32_t;

  [[nodiscard]] auto getB() const -> f32_t;

  [[nodiscard]] auto getLR() const -> f32_t;

  [[nodiscard]] auto getTB() const -> f32_t;

#pragma endregion

  friend auto operator<<(std::ostream &out, const BoxArea &area) -> std::ostream & {
    return out << std::fixed << std::setprecision(3) << "{"
               << "l:" << area.getL() << ", "
               << "r:" << area.getR() << ", "
               << "t:" << area.getT() << ", "
               << "b:" << area.getB() << "}";
  }

private:
  AreaType type_;
  std::array<f32_t, NUM_OF_EDGES> edges_;
};

}  // namespace sway::ui

#endif  // SWAY_UI_AREA_BOXAREA_HPP
