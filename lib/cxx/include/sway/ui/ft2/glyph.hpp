#ifndef SWAY_UI_FT2_GLYPH_HPP
#define SWAY_UI_FT2_GLYPH_HPP

#include <sway/core.hpp>

#include <freetype/ftstroke.h>
#include <ft2build.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(ft2)

class Glyph {
public:
  Glyph() {}

  ~Glyph() = default;

private:
  FT_Error error_;
  FT_Face face_;
  FT_GlyphSlot slot_;
};

NAMESPACE_END(ft2)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_FT2_GLYPH_HPP
