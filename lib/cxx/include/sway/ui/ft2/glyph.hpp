#ifndef SWAY_UI_FT2_GLYPH_HPP
#define SWAY_UI_FT2_GLYPH_HPP

#include <sway/core.hpp>
#include <sway/ui/ft2/errormacros.hpp>
#include <sway/ui/ft2/face.hpp>

#include <freetype/ftglyph.h>
#include <freetype/ftstroke.h>
#include <ft2build.h>
#include <optional>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(ft2)

struct FontGlyphId {
  u32_t idx;
  s8_t code;

  FontGlyphId(FT_Face face, s8_t charcode)
      : idx(FT_Get_Char_Index(face, charcode))
      , code(charcode) {}
};

class FontGlyph {
public:
  FontGlyph(std::shared_ptr<Face> face)
      : face_(face) {}

  ~FontGlyph() = default;

  static auto load(FT_Face face, FontGlyphId sym) -> std::optional<FT_GlyphSlot> {
    bool success = CHECK_RESULT(FT_Load_Glyph(face, sym.idx, FT_LOAD_DEFAULT));
    if (!success) {
      return std::nullopt;
    }

    return std::make_optional<FT_GlyphSlot>(face->glyph);
  }

private:
  std::shared_ptr<Face> face_;
};

NAMESPACE_END(ft2)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_FT2_GLYPH_HPP
