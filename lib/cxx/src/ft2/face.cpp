#include <sway/ui/ft2/errormacros.hpp>
#include <sway/ui/ft2/face.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(ft2)

Face::Face(FT_Library lib, lpcstr_t filepath, u32_t idx)
    : face_(nullptr) {
  auto success = CHECK_RESULT(FT_New_Face(lib, filepath, idx, &face_));
  if (!success) {
    // Empty
  }
}

Face::Face(FT_Library lib, lpcstr_t data, u32_t size, u32_t idx)
    : face_(nullptr) {
  auto success = CHECK_RESULT(FT_New_Memory_Face(lib, (FT_Byte *)data, size, idx, &face_));
  if (!success) {
    // Empty
  }

  FT_Set_Pixel_Sizes(face_, 64, 0);

  // const int sizes[] = {240, 480, 720, 1080, 2160, 4096, 8192};
  // const int marginSizes[] = {16, 32, 64, 128, 256};

  // for (auto i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
  //   printf("Body: %i (%dP)\n", (int)std::round((f64_t)sizes[i] * 0.1), sizes[i]);
  // }

  // int charSize = std::round((f64_t)sizes[4] * 0.1);
  // FT_Set_Char_Size(face_, charSize * 64, 0, 64, 0);
}

Face::~Face() {
  FT_Done_Face(face_);
  face_ = nullptr;
}

NAMESPACE_END(ft2)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
