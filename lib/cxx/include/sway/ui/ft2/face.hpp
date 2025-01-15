#ifndef SWAY_UI_FT2_FACE_HPP
#define SWAY_UI_FT2_FACE_HPP

#include <sway/ui/_stdafx.hpp>

namespace sway::ui {

/**
 * @ingroup ft2
 * @{
 */

class Face {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  Face(FT_Library lib, lpcstr_t filepath, u32_t idx);

  Face(FT_Library lib, lpcstr_t data, u32_t numBytes, u32_t idx);

  ~Face();

  /** @} */
#pragma endregion

  [[nodiscard]] auto data() const -> FT_Face { return face_; }

  [[nodiscard]] auto getBitmap() const -> FT_Bitmap { return face_->glyph->bitmap; }

public:
  FT_Face face_;
};

/** @} */  // ingroup ft2

}  // namespace sway::ui

#endif  // SWAY_UI_FT2_FACE_HPP
