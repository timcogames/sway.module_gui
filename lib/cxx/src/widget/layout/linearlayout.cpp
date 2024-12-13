#include <sway/ui/builder.hpp>
#include <sway/ui/widget/layout/linearlayout.hpp>

#include <numeric>  // reduce

NS_BEGIN_SWAY()
NS_BEGIN(ui)

LinearLayout::LinearLayout(BuilderTypedefs::Ptr_t builder, Orientation orien)
    : Layout(builder, orien) {}

void LinearLayout::build() {
  auto operation = [&, layout = this](
                       math::point2f_t accum, core::container::Node::SharedPtr_t node) mutable -> math::point2f_t {
    auto child = cast<Widget>(node);
    const auto boundingSize = child->getSize();

    child->setOffset(accum);

    if (layout->getOrientation() == Orientation::HORZ) {
      accum.setX(accum.getX() + boundingSize.getW());
    } else if (layout->getOrientation() == Orientation::VERT) {
      accum.setY(accum.getY() + boundingSize.getH());
    }

    return accum;
  };

  std::reduce(std::begin(getChildNodes()), std::end(getChildNodes()), math::point2f_zero, operation);
}

NS_END()  // namespace ui
NS_END()  // namespace sway
