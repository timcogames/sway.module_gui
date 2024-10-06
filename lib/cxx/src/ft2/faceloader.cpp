#include <sway/ui/ft2/faceloader.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)
NS_BEGIN(ft2)

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

NS_END()  // namespace ft2
NS_END()  // namespace ui
NS_END()  // namespace sway
