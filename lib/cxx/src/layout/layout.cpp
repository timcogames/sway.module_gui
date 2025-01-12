#include <sway/ui/builder.hpp>
#include <sway/ui/layout/specs/linearlayout.hpp>

namespace sway::ui {

auto Layout::getCellSize(ElementTypedefs::Ptr_t elem) -> math::size2f_t {
  return elem->getAreaHolder().getContentSize() / elem->getNumOfChildNodes();
}

Layout::Layout(BuilderTypedefs::Ptr_t builder, Orientation orien)
    : LayoutItem()
    , Orientable(orien) {
  setMouseFilter(ois::MouseFilter::PASS);
}

}  // namespace sway::ui
