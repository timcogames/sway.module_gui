#include <sway/gapi.hpp>
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

void Font::create(FT_Face face, lpcstr_t symbols, bool hinted, bool antialiased) {
  s8_t charcode;
  for (auto i = 0; i < strlen(symbols); i++) {
    charcode = (s8_t)symbols[i];

    if (FT_Load_Glyph(face, FT_Get_Char_Index(face, charcode), FT_LOAD_DEFAULT)) {
      continue;
    }

    if (FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL)) {
      continue;
    }

    FT_GlyphSlot slot = face->glyph;
    FT_Bitmap bitmap = slot->bitmap;

    gapi::TextureCreateInfo createInfo;
    createInfo.target = gapi::TextureTarget::TEX_2D;
    createInfo.size = math::size2i_t(bitmap.width, bitmap.rows);
    // createInfo.arraySize
    createInfo.format = gapi::PixelFormat::R;
    createInfo.internalFormat = gapi::PixelFormat::R;
    createInfo.dataType = core::ValueDataType::UBYTE;
    createInfo.pixels = (s8_t *)bitmap.buffer;
    createInfo.mipLevels = 0;
    // createInfo.sampleCount

    // gapi::Texture *texture = image->getTexture();
    // texture->setUnpackAlignement(1);
    // texture->create(createInfo, false);
    // texture->setUnpackAlignement(4);

    auto t = slot->bitmap_top;
    auto l = slot->bitmap_left;
    auto w = bitmap.width;
    auto h = bitmap.rows;

    GlyphInfo fontCharacter;
    fontCharacter.bearing = math::vec2i_t(l, t);
    fontCharacter.size = math::vec2i_t(w, h);
    fontCharacter.advance = math::vec2i_t(FT_PosToInt(slot->advance.x), FT_PosToInt(slot->advance.y));
    // fontCharacter.image = image;

    // glyphInfo_.insert(std::pair<UInt32, LGLYPH_INFO>(charcode, fontCharacter));
  }
}

NAMESPACE_END(ft2)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
