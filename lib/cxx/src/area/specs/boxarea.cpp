#include <sway/ui/area/specs/boxarea.hpp>

namespace sway::ui {

BoxArea::BoxArea(AreaType type)
    : type_(type) {
  resetEdges();
}

auto BoxArea::getType() const -> AreaType { return type_; }

void BoxArea::resetEdges() { edges_.fill(0.0F); }

void BoxArea::set(math::RectEdge::Enum edge, f32_t val) { edges_[core::toBase(edge)] = val; }

void BoxArea::set(f32_t l, f32_t t, f32_t r, f32_t b) {
  set(math::RectEdge::Enum::IDX_L, l);
  set(math::RectEdge::Enum::IDX_T, t);
  set(math::RectEdge::Enum::IDX_R, r);
  set(math::RectEdge::Enum::IDX_B, b);
}

auto BoxArea::at(math::RectEdge::Enum edge) const -> const f32_t & { return edges_[core::toBase(edge)]; }

auto BoxArea::at(math::RectEdge::Enum edge) -> f32_t & { return edges_[core::toBase(edge)]; }

auto BoxArea::getL() const -> f32_t { return at(math::RectEdge::Enum::IDX_L); }

auto BoxArea::getT() const -> f32_t { return at(math::RectEdge::Enum::IDX_T); }

auto BoxArea::getR() const -> f32_t { return at(math::RectEdge::Enum::IDX_R); }

auto BoxArea::getB() const -> f32_t { return at(math::RectEdge::Enum::IDX_B); }

auto BoxArea::getLR() const -> f32_t { return getL() + getR(); }

auto BoxArea::getTB() const -> f32_t { return getT() + getB(); }

}  // namespace sway::ui
