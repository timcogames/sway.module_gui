#ifndef SWAY_UI_FT2_FACE_HPP
#define SWAY_UI_FT2_FACE_HPP

#include <sway/ui/_stdafx.hpp>

namespace sway::ui {
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
}  // namespace sway::ui

#endif  // SWAY_UI_FT2_FACE_HPP
