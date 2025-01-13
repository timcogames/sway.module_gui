#include <sway/core.hpp>
#include <sway/ui/builder.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/backdrop.hpp>
#include <sway/ui/zindex.hpp>

#include <memory>
#include <string>
#include <unordered_map>

namespace sway::ui {

Backdrop::Backdrop(BuilderPtr_t builder)
    : Widget(builder) {
  this->setPosition(ElementPosition::FIXED);
}

void Backdrop::update() {}

void Backdrop::repaint(PainterSharedPtr_t painter) {
  auto offset = this->getOffset().computed;
  painter->drawRect(math::rect4f_t(offset.getX(), offset.getY(), this->getSize()), this->getBackgroundColor(),
      getZIndex((i32_t)core::toBase(ZIndex::BACKDROP)));

  Widget::repaint(painter);
}

}  // namespace sway::ui
