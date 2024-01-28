#include <sway/ui/ft2/font.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(ft2)

Font::Font() {
  // Empty
}

Font::~Font() {
  // Empty
}

void Font::create(FT_Face face, lpcstr_t symbols, bool hinted, bool antialiased) {}

NAMESPACE_END(ft2)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
