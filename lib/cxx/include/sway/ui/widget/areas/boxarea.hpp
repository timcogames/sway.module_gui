#ifndef SWAY_UI_WIDGETS_AREAS_BOXAREA_HPP
#define SWAY_UI_WIDGETS_AREAS_BOXAREA_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ui/widget/area.hpp>
#include <sway/ui/widget/areatypes.hpp>
#include <sway/ui/widget/typedefs.hpp>

#include <array>
#include <iostream>  // std::ostream
#include <memory>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class BoxArea : public Area {
  DECLARE_CLASS_POINTER_ALIASES(BoxArea)

public:
#pragma region "Ctors/Dtor"

  BoxArea(AreaType type);

  virtual ~BoxArea() = default;

#pragma endregion

#pragma region "Override Area methods"

  MTHD_OVERRIDE(auto type() const -> AreaType);

#pragma endregion

  void resetEdges();

  void set(math::RectEdge::Enum edge, f32_t val);

  void set(f32_t l, f32_t t, f32_t r, f32_t b);

  auto at(math::RectEdge::Enum edge) const -> const f32_t &;

  auto at(math::RectEdge::Enum edge) -> f32_t &;

  [[nodiscard]]
  auto getL() const -> f32_t;

  [[nodiscard]]
  auto getT() const -> f32_t;

  [[nodiscard]]
  auto getR() const -> f32_t;

  [[nodiscard]]
  auto getB() const -> f32_t;

  [[nodiscard]]
  auto getLR() const -> f32_t;

  [[nodiscard]]
  auto getTB() const -> f32_t;

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

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGETS_AREAS_BOXAREA_HPP
