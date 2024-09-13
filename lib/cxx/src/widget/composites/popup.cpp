#include <sway/core.hpp>
#include <sway/ui/builder.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/popup.hpp>
#include <sway/ui/zindex.hpp>

#include <memory>
#include <string>
#include <unordered_map>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

Popup::Popup(BuilderPtr_t builder)
    : Widget(builder) {}

Popup::~Popup() {}

void Popup::update() {}

void Popup::repaint(Painter::SharedPtr_t painter) {
  auto offset = this->getOffset().computed;
  painter->drawRect(math::rect4f_t(offset.getX(), offset.getY(), this->getSize()), this->getBackgroundColor(),
      getZIndex((f32_t)core::detail::toBase(ZIndex::DIALOG)));

  Widget::repaint(painter);
}

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
