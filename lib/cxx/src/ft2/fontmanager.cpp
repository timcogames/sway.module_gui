#include <sway/ui/ft2/fontmanager.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(ft2)

FontManager::FontManager()
    : lib_(nullptr)
    , initialized_(false) {
  // Empty
}

FontManager::~FontManager() { FT_Done_FreeType(lib_); }

void FontManager::init() {
  if (initialized_) {
    return;
  }

  auto error = FT_Init_FreeType(&lib_);
  initialized_ = true;
}

NAMESPACE_END(ft2)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
