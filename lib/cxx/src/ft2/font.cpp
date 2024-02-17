#include <sway/gapi.hpp>
#include <sway/ui/ft2/font.hpp>

#include <algorithm>  // std::max

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(ft2)

Font::Font(std::shared_ptr<Face> face, math::size2i_t atlasSize)
    : face_(face)
    , atlasSize_(atlasSize) {}

void Font::create(lpcstr_t charcodes, bool hinted, bool antialiased) {
  for (auto i = 0; i < strlen(charcodes); i++) {
    if (hasCharInfo(charcodes[i])) {
      continue;
    }

    FontGlyphId glyphId(face_->data(), charcodes[i]);
    glyphs_.push_back(glyphId);

    auto slot = FontGlyph::load(face_->data(), glyphId);
    if (!slot.has_value()) {
      continue;
    }

    auto info = getCharMetrics(slot.value());
    info.symidx = glyphId.idx;

    FT_Glyph glyph;
    FT_Get_Glyph(slot.value(), &glyph);
    FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, 0, 1);

    FT_BitmapGlyph bitmapGlyph = (FT_BitmapGlyph)glyph;
    FT_Bitmap *bitmap = &(bitmapGlyph)->bitmap;

    cache_[glyphId.code] = info;

    maxSize_ = this->computeMaxSize_(bitmap, maxSize_);
  }
}

auto Font::computeMaxSize_(FT_Bitmap *bitmap, math::size2i_t size) -> math::size2i_t {
  // clang-format off
  return {
    std::max<s32_t>(size.getW(), math::util::powerOf2(bitmap->width)),
    std::max<s32_t>(size.getH(), math::util::powerOf2(bitmap->rows))
  };  // clang-format on
}

auto Font::getBitmapData(FontGlyphId sym) -> BitmapInfo {
  auto slot = FontGlyph::load(face_->data(), sym);
  if (!slot.has_value()) {
    // Empty
  }

  FT_Glyph glyph;
  FT_Get_Glyph(slot.value(), &glyph);

  FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, 0, 1);
  auto *bitmap = &((FT_BitmapGlyph)glyph)->bitmap;

  const auto texWdt = math::util::powerOf2(bitmap->width);
  const auto texHgt = math::util::powerOf2(bitmap->rows);

  auto x = (float)bitmap->width / (float)texWdt;
  auto y = (float)bitmap->rows / (float)texHgt;

  const auto texPitch = bitmap->pitch;
  const auto texAreaSize = texWdt * texHgt;
  const auto texPixelComponents = 2;

  auto *texData = (u8_t *)malloc(texAreaSize * texPixelComponents * sizeof(u8_t));
  for (auto y = 0; y < texHgt; y++) {
    for (auto x = 0; x < texWdt; x++) {
      auto texPixelIdx = texPixelComponents * (x + texWdt * y);

      texData[texPixelIdx] = 255;

      if (x >= bitmap->width || y >= bitmap->rows) {
        texData[texPixelIdx + 1] = 0;
      } else {
        texData[texPixelIdx + 1] = (bitmap->buffer[x + bitmap->width * y]);
      }
    }
  }

  BitmapInfo bi;
  bi.data = texData;
  bi.size = math::size2i_t(texWdt, texHgt);

  free(texData);
  return bi;
}

auto Font::getCharInfo(s8_t code) const -> std::optional<CharInfo> {
  const auto &iter = cache_.find(code);
  if (iter != cache_.end()) {
    return std::make_optional<CharInfo>((*iter).second);
  }

  return std::nullopt;
}

[[nodiscard]]
auto Font::hasCharInfo(s8_t code) const -> bool {
  return cache_.find(code) != cache_.end();
}

auto Font::getCharMetrics(FT_GlyphSlot slot) -> CharInfo {
  auto metrics = slot->metrics;

  CharInfo info;
  info.size = math::size2i_t(metrics.width, metrics.height) / 64;
  info.bearing = math::vec2i_t(metrics.horiBearingX >> 6, metrics.horiBearingY >> 6);
  info.advance = metrics.horiAdvance / 64;
  auto advanceX = slot->advance.x >> 6;
  auto advanceY = slot->advance.y >> 6;

  return info;
}

NAMESPACE_END(ft2)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
