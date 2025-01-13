#include <sway/core.hpp>
#include <sway/ui/builder.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/popup.hpp>
#include <sway/ui/zindex.hpp>

#include <memory>
#include <string>
#include <unordered_map>

namespace sway::ui {

Popup::Popup(BuilderPtr_t builder)
    : Widget(builder) {}

Popup::~Popup() {}

void Popup::update() {}

void Popup::repaint(PainterSharedPtr_t painter) {
  auto offset = this->getOffset().computed;
  painter->drawRect(math::rect4f_t(offset.getX(), offset.getY(), this->getSize()), this->getBackgroundColor(),
      getZIndex((i32_t)core::toBase(ZIndex::DIALOG)));

  Widget::repaint(painter);
}

}  // namespace sway::ui
