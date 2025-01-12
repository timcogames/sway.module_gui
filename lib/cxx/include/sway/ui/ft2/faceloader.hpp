#ifndef SWAY_UI_FT2_FACELOADER_HPP
#define SWAY_UI_FT2_FACELOADER_HPP

#include <sway/core.hpp>
#include <sway/rms.hpp>
#include <sway/ui/ft2/face.hpp>

#include <freetype/ftstroke.h>
#include <ft2build.h>

namespace sway::ui {
NS_BEGIN(ft2)

struct ObjectFetchResponse : public rms::FetchResponse {
  ObjectFetchResponse(lpcstr_t data, u32_t numBytes)
      : rms::FetchResponse(data, numBytes) {}

  auto serialize(FT_Library lib) -> std::shared_ptr<Face> {
    return std::make_shared<Face>(lib, this->data, this->numBytes, 0);
  }
};

class FaceLoader : public rms::Fetcher {
public:
  FaceLoader(const std::string &url);

  virtual ~FaceLoader() = default;

  MTHD_OVERRIDE(void fetch());

private:
  // std::shared_ptr<Face> faceResponse_;
};

NS_END()  // namespace ft2
}  // namespace sway::ui

#endif  // SWAY_UI_FT2_FACELOADER_HPP
