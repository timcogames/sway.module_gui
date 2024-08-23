#ifndef SWAY_UI_WIDGETS_ELEMENT_HPP
#define SWAY_UI_WIDGETS_ELEMENT_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ui/widget/elementareaholder.hpp>
#include <sway/ui/widget/elementpositions.hpp>
#include <sway/ui/widget/types.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

class Element {
public:
#pragma region "Ctors/Dtor"

  Element();

  ~Element() = default;

  void setOffset(ElementPosition pos, const math::point2f_t &pnt) {
    position_ = pos;
    offset_ = pnt;
  }

  void updateOffset() {
    if (position_ == ElementPosition::ABSOLUTE || position_ == ElementPosition::FIXED) {
    } else {
    }
  }

#pragma endregion

protected:
  ElementAreaHolder elemAreaHolder_;
  ElementPosition position_;
  math::point2f_t offset_;
};

NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGETS_ELEMENT_HPP
