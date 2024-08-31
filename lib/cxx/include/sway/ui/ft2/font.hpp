#ifndef SWAY_UI_FT2_FONT_HPP
#define SWAY_UI_FT2_FONT_HPP

#include <sway/core.hpp>
#include <sway/render.hpp>
#include <sway/ui/ft2/face.hpp>
#include <sway/ui/ft2/glyph.hpp>

#include <freetype/ftstroke.h>
#include <ft2build.h>
#include <nlohmann/json.hpp>
#include <optional>
#include <unordered_map>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(ft2)

#define NUM_GREYMAP_CMPTS 2

class Greymap {
public:
  static auto initial(const math::size2i_t &size) {
    Greymap data(size);
    for (auto y = 0; y < size.getH(); y++) {
      for (auto x = 0; x < size.getW(); x++) {
        data.at(x, y, 0) = 255;
      }
    }

    return data;
  }

  Greymap(const math::size2i_t &size)
      : pixels_((u8_t *)malloc(NUM_GREYMAP_CMPTS * size.area() * sizeof(u8_t)))
      , stride_(size.getW()) {}

  ~Greymap() { free(pixels_); }

  auto at(u32_t x, u32_t y, u32_t cmpt) -> u8_t & {
    const auto idx = NUM_GREYMAP_CMPTS * (y * stride_ + x);
    return pixels_[idx + cmpt];
  }

  auto get() -> u8_t * { return pixels_; }

private:
  u8_t *pixels_;
  u32_t stride_;
};

// struct GlyphInfo {
//   u32_t texID;
//   math::vec2i_t size;
//   math::vec2i_t bearing;
//   math::vec2i_t advance;
//   std::shared_ptr<render::Image> image;
// };

struct BitmapInfo {
  Greymap data;
  math::size2i_t bitmapSize;

  BitmapInfo(const math::size2i_t &size)
      : data(Greymap::initial(size)) {}
};

struct CharInfo {
  math::size2i_t size;
  i32_t advance;
  math::vec2i_t bitmapGlyphOffset;
  math::rect4f_t rect;
};

// struct FontCharacter {
//   math::vec2i_t size;
//   math::vec2i_t bearing;
//   uint32_t advance;
//   std::array<math::vec2f_t, 4> uvs;
// };

// struct TextLayout {
//   math::vec2i_t size;
// };

struct FontInfo {
  f32_t height;
  f32_t descender;
  f32_t ascender;
  f32_t lineSpacing;
  f32_t lineGap;
  f32_t maxAdvanceWidth;
};

struct FontStyle {
  math::Color<u8_t> foreground = math::Color<u8_t>(0xFF, 0xFF, 0xFF, 0xFF);
  math::Color<u8_t> background = math::Color<u8_t>(0xFF, 0xFF, 0xFF, 0x00);
};

struct FontGlyphDescriptor {
  s8_t *data = nullptr;
  f32_t x = -1, y = -1;
  u32_t advance;
  i32_t top;
  i32_t left;
  u32_t rows;
  u32_t width;
};

class Font {
public:
  using SharedPtr_t = std::shared_ptr<Font>;

  static void toJson(nlohmann::json &jdata, const FontGlyphDescriptor &glyph) {
    // clang-format off
    jdata = nlohmann::json{
      {"a", glyph.advance}, 
      {"x", glyph.x}, 
      {"y", glyph.y}, 
      {"t", glyph.top}, 
      {"l", glyph.left},
      {"r", glyph.rows}, 
      {"w", glyph.width}};
    // clang-format on
  }

  static void fromJson(nlohmann::json &jdata, FontGlyphDescriptor &glyph) {
    jdata.at("x").get_to(glyph.x);
    jdata.at("y").get_to(glyph.y);
    jdata.at("t").get_to(glyph.top);
    jdata.at("l").get_to(glyph.left);
    jdata.at("r").get_to(glyph.rows);
    jdata.at("w").get_to(glyph.width);
    jdata.at("a").get_to(glyph.advance);
  }

  Font(std::shared_ptr<Face> face, math::size2i_t atlasSize, math::size2i_t atlasMarginSize);

  ~Font() = default;

  void setHeight(u32_t height);

  void create(lpcstr_t symbols, bool hinted, bool antialiased);

  auto getAtlasSize() const -> math::size2i_t { return atlasSize_; }

  auto getBitmapData(FontGlyphId sym) -> BitmapInfo;

  void drawBitmap(FT_Bitmap *bitmap, Greymap data);

  auto getCharInfo(s8_t code) const -> std::optional<CharInfo>;

  auto hasCharInfo(s8_t code) const -> bool;

  auto getCharMetrics(FT_GlyphSlot slot) -> CharInfo;

  auto getFace() -> FT_Face { return face_->data(); }

  auto computeMaxSize_(FT_Bitmap *bitmap, math::size2i_t size) -> math::size2i_t;

public:
  std::shared_ptr<Face> face_;
  math::size2i_t atlasSize_;
  math::size2i_t atlasMarginSize_;

  FontInfo info_;
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
