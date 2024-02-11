#include <sway/ui/ft2/faceloader.hpp>
#include <sway/ui/ft2/fontmanager.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(ft2)

#define ASCII_SIZE 256
// lpcstr_t SymbolSet = "1234567890-=!@#$%^&*()_+\\|/><,.?~`';: "
//                      "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЪЫЭЮЯ"
//                      "абвгдеёжзийклмнопрстуфхцчшщьъыэюя"
//                      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//                      "abcdefghijklmnopqrstuvwxyz";

lpcstr_t SymbolSet = "1234567890-=!@#$%^&*()_+\\|/><,.?~`';: "
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                     "abcdefghijklmnopqrstuvwxyz";

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

void FontManager::load(std::function<void()> fn, std::shared_ptr<rms::FetcherQueue> fetcherQueue,
    const std::string &name, const std::string &filepath) {
  auto loader = std::make_shared<FaceLoader>(lib_, filepath.c_str());
  loader->setCallback([this, fn, name](rms::FetchResponse *resp) -> void {
    auto *response = static_cast<ObjectFetchResponse *>(resp);
    auto object = response->serialize(lib_);

    cache_.insert(std::make_pair(name, object));
    fn();
  });

  fetcherQueue->add(loader);
}

auto FontManager::addFont(const std::string &name) -> std::shared_ptr<Font> {
  auto iter = cache_.find(name);
  if (iter == cache_.end()) {
    return nullptr;
  }

  auto texAtlasSize = math::size2i_t(624, 624);
  auto font = std::make_shared<Font>(iter->second, texAtlasSize);
  font->create(SymbolSet, false, true);

  fonts_.insert(std::make_pair(name, font));
  return font;
}

auto FontManager::find(const std::string &name) -> std::shared_ptr<Font> {
  auto iter = fonts_.find(name);
  if (iter != fonts_.end()) {
    return iter->second;
  }

  return nullptr;
}

void FontManager::removeFont() { fonts_.clear(); }

NAMESPACE_END(ft2)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
