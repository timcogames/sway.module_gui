#include <sway/ui/builder.hpp>
#include <sway/ui/widget/linearlayout.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)
NS_BEGIN(widget)

Layout::Layout(BuilderPtr_t builder, Orientation orien)
    : Widget(builder)
    , Orientable(orien) {
  setMouseFilter(ois::MouseFilter::PASS);
}

NS_END()  // namespace widget
NS_END()  // namespace ui
NS_END()  // namespace sway
