#ifndef SWAY_UI_FT2_FONTMANAGER_HPP
#define SWAY_UI_FT2_FONTMANAGER_HPP

#include <sway/core.hpp>
#include <sway/ui/ft2/face.hpp>

#include <freetype/ftstroke.h>
#include <ft2build.h>
#include <string>
#include <unordered_map>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(ft2)

class FontManager {
public:
  FontManager();

  ~FontManager();

  void initLibrary();

  void freeLibrary();

  void load(std::shared_ptr<rms::FetcherQueue> fetcherQueue, const std::string &name, const std::string &filepath);

private:
  FT_Library lib_;
  bool initialized_;

  std::unordered_map<std::string, std::shared_ptr<Face>> cache_;
};

NAMESPACE_END(ft2)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_FT2_FONTMANAGER_HPP
