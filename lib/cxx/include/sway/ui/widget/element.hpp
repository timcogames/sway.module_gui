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

  void setPosition(ElementPosition pos) { position_ = pos; }

  void setOffset(const math::point2f_t &pnt);

  auto getOffset(ElementPosition pos) -> math::point2f_t;

  void updateOffset();

#pragma endregion

protected:
  ElementAreaHolder areaHolder_;
  ElementPosition position_;
  math::point2f_t offset_;
  bool offsetDirty_;
};

NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGETS_ELEMENT_HPP
