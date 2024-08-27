#ifndef SWAY_UI_WIDGETS_ELEMENT_HPP
#define SWAY_UI_WIDGETS_ELEMENT_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ui/widget/elementareaholder.hpp>
#include <sway/ui/widget/elementpositions.hpp>
#include <sway/ui/widget/types.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

class Element : public core::container::Node  // math::Transform<core::container::Node, f32_t>
{
public:
#pragma region "Ctors/Dtor"

  Element();

  ~Element() = default;

  void setPosition(ElementPosition pos);

  [[nodiscard]]
  auto getPosition() const -> ElementPosition;

  void setOffset(const math::point2f_t &pnt);

  void setOffset(f32_t x, f32_t y);

  [[nodiscard]]
  auto getOffset(ElementPosition pos) const -> math::point2f_t;

  [[nodiscard]]
  auto isOffsetDirty() const -> bool;

  void updateOffset();

  [[nodiscard]]
  auto getAreaHolder() const -> ElementAreaHolder;

  [[nodiscard]]
  auto getInnerSize() const -> math::size2f_t;

  [[nodiscard]]
  auto getOuterSize() const -> math::size2f_t;

  [[nodiscard]]
  auto getOuterSizeWithMargin() const -> math::size2f_t;

#pragma endregion

private:
  ElementAreaHolder holder_;
  ElementPosition position_;
  math::point2f_t offset_;
  bool offsetDirty_;
};

NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGETS_ELEMENT_HPP
