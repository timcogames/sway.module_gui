#ifndef SWAY_UI_WIDGETS_ELEMENTAREAHOLDER_HPP
#define SWAY_UI_WIDGETS_ELEMENTAREAHOLDER_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ui/widget/area.hpp>
#include <sway/ui/widget/areatypes.hpp>
#include <sway/ui/widget/types.hpp>

#include <array>
#include <memory>
#include <optional>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

class ElementAreaHolder : public AreaHolder_t {
  DECLARE_CLASS_POINTER_ALIASES(ElementAreaHolder)

public:
#pragma region "Ctors/Dtor"

  ElementAreaHolder();

  ~ElementAreaHolder() = default;

#pragma endregion

  auto getAreaIndex(AreaType type) const -> i32_t;

  template <AreaType TYPE>
  auto getAreaIndex() const -> i32_t;

  auto getArea(AreaType type) const -> std::optional<Area::SharedPtr_t>;

  template <AreaType TYPE, typename OUT = OutputAreaType_t<TYPE>>
  auto getArea() const -> std::optional<std::shared_ptr<OUT>>;

  template <AreaType TYPE, math::RectEdge EDGE>
  void setEdge(f32_t size);

  // template <math::RectEdge EDGE>
  // auto getEdge(std::optional<BoxArea::SharedPtr_t> area) const -> f32_t;

  template <math::RectEdge EDGE>
  auto getEdge(Area::SharedPtr_t area) const -> f32_t;

  template <AreaType TYPE, math::RectEdge EDGE>
  auto getEdge() const -> f32_t;

  template <AreaType TYPE>
  auto getPosition() const -> math::vec2f_t;

  template <AreaType TYPE>
  auto getSize() const -> math::size2f_t;

  [[nodiscard]]
  auto getContentSize() const -> math::size2f_t;
};

NAMESPACE_END(ui)
NAMESPACE_END(sway)

#include <sway/ui/widget/elementareaholder.inl>

#endif  // SWAY_UI_WIDGETS_ELEMENTAREAHOLDER_HPP
