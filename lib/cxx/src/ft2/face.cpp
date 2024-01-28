#include <sway/ui/ft2/face.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(ft2)

Face::Face(FT_Library lib, lpcstr_t filepath, u32_t idx)
    : face_(nullptr) {
  FT_Error error = FT_New_Face(lib, filepath, idx, &face_);
  if (error != FT_Err_Ok) {
    printf("Can't load font from file '%s', error 0x%x\n", filepath, error);
  }
}

Face::Face(FT_Library lib, const u8_t *data, u32_t size, u32_t idx)
    : face_(nullptr) {
  FT_Error error = FT_New_Memory_Face(lib, data, size, idx, &face_);
  if (error != FT_Err_Ok) {
    printf("Can't load font from memory, error 0x%x\n", error);
  }
}

Face::~Face() {
  FT_Done_Face(face_);
  face_ = nullptr;
}

NAMESPACE_END(ft2)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
