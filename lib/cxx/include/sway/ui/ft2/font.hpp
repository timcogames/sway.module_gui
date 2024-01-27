#ifndef SWAY_UI_FT2_FONT_HPP
#define SWAY_UI_FT2_FONT_HPP

#include <sway/core.hpp>

#include <freetype/ftstroke.h>
#include <ft2build.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(ft2)

class Font {
public:
  Font();

  ~Font();

private:
  FT_Face face_;
};

NAMESPACE_END(ft2)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_FT2_FONT_HPP
