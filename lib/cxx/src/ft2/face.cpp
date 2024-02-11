#include <sway/ui/ft2/errormacros.hpp>
#include <sway/ui/ft2/face.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(ft2)

Face::Face(FT_Library lib, lpcstr_t filepath, u32_t idx)
    : face_(nullptr) {
  auto success = CHECK_RESULT(FT_New_Face(lib, filepath, idx, &face_));
  if (!success) {
    // printf("Can't load font from file '%s', error 0x%x\n", filepath, error);
  }
}

Face::Face(FT_Library lib, lpcstr_t data, u32_t size, u32_t idx)
    : face_(nullptr) {
  auto success = CHECK_RESULT(FT_New_Memory_Face(lib, (FT_Byte *)data, size, idx, &face_));
  if (!success) {
    // printf("Can't load font from memory, error 0x%x\n", error);
  }

  int pixelSize = 32;
  FT_Set_Pixel_Sizes(face_, pixelSize, 0);
}

Face::~Face() {
  FT_Done_Face(face_);
  face_ = nullptr;
}

NAMESPACE_END(ft2)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
