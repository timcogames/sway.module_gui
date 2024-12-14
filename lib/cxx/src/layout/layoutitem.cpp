#include <sway/ui/layout/layoutitem.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

LayoutItem::LayoutItem()
    : mouseFilter_(ois::MouseFilter::Enum::STOP) {}

NS_END()  // namespace ui
NS_END()  // namespace sway
