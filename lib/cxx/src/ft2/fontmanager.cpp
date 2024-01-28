#include <sway/ui/ft2/fontmanager.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(ft2)

FontManager::FontManager()
    : lib_(nullptr)
    , initialized_(false) {
  initLibrary();
}

FontManager::~FontManager() { freeLibrary(); }

void FontManager::initLibrary() {
  if (initialized_) {
    return;
  }

  if (FT_Init_FreeType(&lib_) != FT_Err_Ok) {
    return;
  }

  initialized_ = true;
}

void FontManager::freeLibrary() { FT_Done_FreeType(lib_); }

void FontManager::load(const std::string &name, const std::string &filepath) {
  cache_.insert(std::make_pair(name, std::make_shared<Face>(lib_, filepath.c_str(), 0)));
}

NAMESPACE_END(ft2)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
