#include <sway/core.hpp>
#include <sway/ui/builder.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/backdrop.hpp>
#include <sway/ui/zindex.hpp>

#include <memory>
#include <string>
#include <unordered_map>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

Backdrop::Backdrop(BuilderPtr_t builder)
    : Widget(builder) {
  this->setPosition(ElementPosition::FIXED);
}

Backdrop::~Backdrop() {}

void Backdrop::update() {}

void Backdrop::repaint(Painter::SharedPtr_t painter) {
  auto offset = this->getOffset().computed;
  painter->drawRect(math::rect4f_t(offset.getX(), offset.getY(), this->getSize()), this->getBackgroundColor(),
      getZIndex((i32_t)core::detail::toBase(ZIndex::BACKDROP)));

  Widget::repaint(painter);
}

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
