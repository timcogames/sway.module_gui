#ifndef SWAY_UI_FT2_FACE_HPP
#define SWAY_UI_FT2_FACE_HPP

#include <sway/core.hpp>
#include <sway/rms.hpp>

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

class FaceLoader : public rms::Fetcher {
public:
  FaceLoader(FT_Library lib, const std::string &url)
      : rms::Fetcher(url)
      , lib_(lib) {}

  ~FaceLoader() {}

  MTHD_OVERRIDE(void fetch()) {
#if EMSCRIPTEN_PLATFORM
    thread_ = std::thread([this]() -> void {
      auto callback = [this](rms::fetch_res_t fetch) {
        faceResponse_ = std::make_shared<Face>(lib_, (const u8_t *)fetch->data, fetch->numBytes, 0);
        fetching_.store(false);
      };

      rms::RemoteFile::fetch(getUrl().c_str(), callback);
    });
#endif
  }

public:
  FT_Library lib_;
  std::shared_ptr<Face> faceResponse_;
};

NAMESPACE_END(ft2)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_FT2_FACE_HPP
