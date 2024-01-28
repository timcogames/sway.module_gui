#ifndef SWAY_UI_FT2_FACE_HPP
#define SWAY_UI_FT2_FACE_HPP

#include <sway/core.hpp>

#include <freetype/ftstroke.h>
#include <ft2build.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(ft2)

class Face {
public:
  Face(FT_Library lib, lpcstr_t filepath, u32_t idx);

  Face(FT_Library lib, const u8_t *data, u32_t size, u32_t idx);

  ~Face();

  [[nodiscard]]
  auto getFamilyName() const -> std::string {
    return face_->family_name;
  }

  [[nodiscard]]
  auto getStyle() const -> std::string {
    return face_->style_name;
  }

private:
  FT_Face face_;
};

NAMESPACE_END(ft2)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_FT2_FACE_HPP
