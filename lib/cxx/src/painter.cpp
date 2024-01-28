#include <sway/ui/painter.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

Painter::Painter() {
  std::array<gapi::VertexSemantic, 3> semantics = {
      gapi::VertexSemantic::POS, gapi::VertexSemantic::COL, gapi::VertexSemantic::TEXCOORD_0};
}

Painter::~Painter() {
  // Empty
}

NAMESPACE_END(ui)
NAMESPACE_END(sway)
