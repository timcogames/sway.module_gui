#ifndef SWAY_UI_FT2_FACELOADER_HPP
#define SWAY_UI_FT2_FACELOADER_HPP

#include <sway/core.hpp>
#include <sway/rms.hpp>
#include <sway/ui/ft2/face.hpp>

#include <freetype/ftstroke.h>
#include <ft2build.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(ft2)

struct ObjectFetchResponse : public rms::FetchResponse {
  ObjectFetchResponse(lpcstr_t data, u32_t numBytes)
      : rms::FetchResponse(data, numBytes) {}

  auto serialize(FT_Library lib) -> std::shared_ptr<Face> {
    return std::make_shared<Face>(lib, this->data, this->numBytes, 0);
  }
};

class FaceLoader : public rms::Fetcher {
public:
  FaceLoader(FT_Library lib, const std::string &url);

  virtual ~FaceLoader() = default;

  MTHD_OVERRIDE(void fetch());

private:
  FT_Library lib_;
  // std::shared_ptr<Face> faceResponse_;
};

NAMESPACE_END(ft2)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_FT2_FACELOADER_HPP
