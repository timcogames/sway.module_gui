#include <sway/ui/widget/areas/contentarea.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

ContentArea::ContentArea(const math::size2f_t &size)
    : size_(size) {}

auto ContentArea::type() const -> AreaType { return AreaType::IDX_CNT; }

void ContentArea::setSize(const math::size2f_t &size) { size_ = size; }

auto ContentArea::getSize() const -> math::size2f_t { return size_; }

NAMESPACE_END(ui)
NAMESPACE_END(sway)
