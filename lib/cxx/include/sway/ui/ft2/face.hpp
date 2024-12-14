#ifndef SWAY_UI_FT2_FACE_HPP
#define SWAY_UI_FT2_FACE_HPP

#include <sway/core.hpp>
#include <sway/rms.hpp>

#include <freetype/ftstroke.h>
#include <ft2build.h>

NS_BEGIN_SWAY()
NS_BEGIN(ui)
NS_BEGIN(ft2)

class Face {
public:
  Face(FT_Library lib, lpcstr_t filepath, u32_t idx);

  Face(FT_Library lib, lpcstr_t data, u32_t numBytes, u32_t idx);

  ~Face();

  [[nodiscard]] auto data() const -> FT_Face { return face_; }

  [[nodiscard]] auto getBitmap() const -> FT_Bitmap { return face_->glyph->bitmap; }

public:
  FT_Face face_;
};

NS_END()  // namespace ft2
NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_FT2_FACE_HPP
