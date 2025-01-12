#include <sway/ui/area/specs/contentarea.hpp>

namespace sway::ui {

ContentArea::ContentArea(const math::size2f_t &size)
    : size_(size) {}

auto ContentArea::getType() const -> AreaType { return AreaType::IDX_CNT; }

void ContentArea::setSize(const math::size2f_t &size) { size_ = size; }

auto ContentArea::getSize() const -> math::size2f_t { return size_; }

}  // namespace sway::ui
