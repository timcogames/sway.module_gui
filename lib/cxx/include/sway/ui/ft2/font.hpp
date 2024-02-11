#ifndef SWAY_UI_FT2_FONT_HPP
#define SWAY_UI_FT2_FONT_HPP

#include <sway/core.hpp>
#include <sway/render.hpp>
#include <sway/ui/ft2/face.hpp>
#include <sway/ui/ft2/glyph.hpp>

#include <freetype/ftstroke.h>
#include <ft2build.h>
#include <optional>
#include <unordered_map>

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

struct BitmapInfo {
  u8_t *data;
  math::size2i_t size;
};

struct CharInfo {
  u32_t symidx;
  math::size2i_t size;
  math::vec2i_t bearing;
  // math::vec2i_t advance;
  s32_t advance;
  // s8_t *data;
};

struct FontCharacter {
  math::vec2i_t size;
  math::vec2i_t bearing;
  uint32_t advance;
  std::array<math::vec2f_t, 4> uvs;
};

// struct TextLayout {
//   math::vec2i_t size;
// };

struct FontStyle {
  math::Color<u8_t> foreground = math::Color<u8_t>(0xFF, 0xFF, 0xFF, 0xFF);
  math::Color<u8_t> background = math::Color<u8_t>(0xFF, 0xFF, 0xFF, 0x00);
};

class Font {
public:
  Font(std::shared_ptr<Face> face, math::size2i_t atlasSize);

  ~Font() = default;

  void create(lpcstr_t symbols, bool hinted, bool antialiased);

  auto getAtlasSize() const -> math::size2i_t { return atlasSize_; }

  auto getBitmapData(FontGlyphId sym) -> BitmapInfo;

  auto getCharInfo(s8_t code) const -> std::optional<CharInfo>;

  auto hasCharInfo(s8_t code) const -> bool;

  auto getCharMetrics(FT_GlyphSlot slot) -> CharInfo;

  auto getFace() -> FT_Face { return face_->data(); }

  // auto computeMetrics_(FT_GlyphSlot slot, math::size2i_t size) -> math::size2i_t;
  auto computeMaxSize_(FT_Glyph glyph, math::size2i_t size) -> math::size2i_t;

public:
  std::shared_ptr<Face> face_;
  math::size2i_t atlasSize_;
  std::map<s8_t, FontCharacter> chars_;
  gapi::TextureCreateInfo createInfo_;

  // TextLayout data_;
  FontStyle style_;

  FT_Matrix matrix_;
  FT_Vector pen_;
  std::unordered_map<s8_t, CharInfo> cache_;

  std::vector<FontGlyphId> glyphs_;
  math::size2i_t maxSize_;
};

NAMESPACE_END(ft2)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_FT2_FONT_HPP
