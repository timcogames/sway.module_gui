#include <sway/ui/builder.hpp>
#include <sway/ui/layout/specs/linearlayout.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

auto Layout::getCellSize(Element *elem) -> math::size2f_t {
  return elem->getAreaHolder().getContentSize() / elem->getNumOfChildNodes();
}

Layout::Layout(BuilderTypedefs::Ptr_t builder, Orientation orien)
    : LayoutItem()
    , Orientable(orien) {
  setMouseFilter(ois::MouseFilter::Enum::PASS);
}

NS_END()  // namespace ui
NS_END()  // namespace sway
