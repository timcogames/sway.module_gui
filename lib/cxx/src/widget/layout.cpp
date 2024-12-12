#include <sway/ui/builder.hpp>
#include <sway/ui/widget/linearlayout.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)
NS_BEGIN(widget)

Layout::Layout(BuilderTypedefs::Ptr_t builder, Orientation orien)
    : Widget(builder)
    , Orientable(orien) {
  setMouseFilter(ois::MouseFilter::Enum::PASS);
}

NS_END()  // namespace widget
NS_END()  // namespace ui
NS_END()  // namespace sway
