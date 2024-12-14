#include <sway/ui/area/specs/contentarea.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

ContentArea::ContentArea(const math::size2f_t &size)
    : size_(size) {}

auto ContentArea::getType() const -> AreaType { return AreaType::IDX_CNT; }

void ContentArea::setSize(const math::size2f_t &size) { size_ = size; }

auto ContentArea::getSize() const -> math::size2f_t { return size_; }

NS_END()  // namespace ui
NS_END()  // namespace sway
