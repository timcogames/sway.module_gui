#ifndef SWAY_UI_FT2_FONTMANAGER_HPP
#define SWAY_UI_FT2_FONTMANAGER_HPP

#include <sway/core.hpp>
#include <sway/ui/ft2/face.hpp>
#include <sway/ui/ft2/font.hpp>

#include <freetype/ftstroke.h>
#include <ft2build.h>
#include <memory>
#include <string>
#include <unordered_map>

NS_BEGIN_SWAY()
NS_BEGIN(ui)
NS_BEGIN(ft2)

class FontManager {
public:
  using Ptr_t = FontManager *;
  using SharedPtr_t = std::shared_ptr<FontManager>;

#pragma region "Ctors/Dtor"

  FontManager();

  ~FontManager();

#pragma endregion

  void initLibrary();

  void freeLibrary();

  void load(std::function<void()> fn, std::shared_ptr<rms::FetcherQueue> fetcherQueue, const std::string &name,
      const std::string &filepath);

  auto addFont(const std::string &name, lpcstr_t symbols, int size, int marginSize) -> Font::SharedPtr_t;

  auto find(const std::string &name) -> Font::SharedPtr_t;

  void removeFont();

private:
  FT_Library lib_;
  bool initialized_;

  std::unordered_map<std::string, std::shared_ptr<Face>> cache_;
  std::unordered_map<std::string, Font::SharedPtr_t> fonts_;
};

NS_END()  // namespace ft2
NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_FT2_FONTMANAGER_HPP
