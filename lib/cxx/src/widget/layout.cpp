#include <sway/ui/builder.hpp>
#include <sway/ui/widget/linearlayout.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

Layout::Layout(Builder::Ptr_t builder, LayoutOrientation orien)
    : Widget(builder)
    , orientation_(orien) {
  setMouseFilter(ois::MouseFilter::PASS);
}

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
