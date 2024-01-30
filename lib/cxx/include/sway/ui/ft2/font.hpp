#ifndef SWAY_UI_FT2_FONT_HPP
#define SWAY_UI_FT2_FONT_HPP

#include <sway/core.hpp>
#include <sway/render.hpp>

#include <freetype/ftstroke.h>
#include <ft2build.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(ft2)

struct GlyphInfo {
  u32_t texID;
  math::vec2i_t size;
  math::vec2i_t bearing;
  math::vec2i_t advance;
  std::shared_ptr<render::Image> image;
};

class Font {
public:
  Font();

  ~Font();

  void create(FT_Face face, lpcstr_t symbols, bool hinted, bool antialiased);

  static inline int FT_PosToInt(int x) { return (((x) + (1 << 5)) >> 6); }

private:
  FT_Face face_;
};

NAMESPACE_END(ft2)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_FT2_FONT_HPP
