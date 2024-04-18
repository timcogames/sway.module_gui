#include <sway/ui/ft2/faceloader.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(ft2)

FaceLoader::FaceLoader(const std::string &url)
    : rms::Fetcher(url) {}

void FaceLoader::fetch() {
#if EMSCRIPTEN_PLATFORM
  thread_ = std::thread([this]() -> void {
    auto callback = [this](rms::fetch_res_t fetch) {
      response_ = new ObjectFetchResponse(fetch->data, fetch->numBytes);
      fetching_.store(false);
    };

    rms::RemoteFile::fetch(getUrl().c_str(), callback);
  });
#endif
}

NAMESPACE_END(ft2)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
