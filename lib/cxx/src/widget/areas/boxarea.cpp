#include <sway/ui/widget/areas/boxarea.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

BoxArea::BoxArea(AreaType type)
    : type_(type) {
  resetEdges();
}

auto BoxArea::type() const -> AreaType { return type_; }

void BoxArea::resetEdges() { edges_.fill(0.0F); }

void BoxArea::set(math::RectEdge edge, f32_t val) { edges_[core::detail::toBase(edge)] = val; }

void BoxArea::set(f32_t l, f32_t t, f32_t r, f32_t b) {
  set(math::RectEdge::IDX_L, l);
  set(math::RectEdge::IDX_T, t);
  set(math::RectEdge::IDX_R, r);
  set(math::RectEdge::IDX_B, b);
}

auto BoxArea::at(math::RectEdge edge) const -> const f32_t & { return edges_[core::detail::toBase(edge)]; }

auto BoxArea::at(math::RectEdge edge) -> f32_t & { return edges_[core::detail::toBase(edge)]; }

auto BoxArea::getL() const -> f32_t { return at(math::RectEdge::IDX_L); }

auto BoxArea::getT() const -> f32_t { return at(math::RectEdge::IDX_T); }

auto BoxArea::getR() const -> f32_t { return at(math::RectEdge::IDX_R); }

auto BoxArea::getB() const -> f32_t { return at(math::RectEdge::IDX_B); }

auto BoxArea::getLR() const -> f32_t { return getL() + getR(); }

auto BoxArea::getTB() const -> f32_t { return getT() + getB(); }

NAMESPACE_END(ui)
NAMESPACE_END(sway)
