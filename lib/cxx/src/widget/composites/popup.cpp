#include <sway/core.hpp>
#include <sway/ui/builder.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/popup.hpp>
#include <sway/ui/zindex.hpp>

#include <memory>
#include <string>
#include <unordered_map>

NS_BEGIN_SWAY()
NS_BEGIN(ui)
NS_BEGIN(widget)

Popup::Popup(BuilderPtr_t builder)
    : Widget(builder) {}

Popup::~Popup() {}

void Popup::update() {}

void Popup::repaint(Painter::SharedPtr_t painter) {
  auto offset = this->getOffset().computed;
  painter->drawRect(math::rect4f_t(offset.getX(), offset.getY(), this->getSize()), this->getBackgroundColor(),
      getZIndex((i32_t)core::detail::toBase(ZIndex::DIALOG)));

  Widget::repaint(painter);
}

NS_END()  // namespace widget
NS_END()  // namespace ui
NS_END()  // namespace sway
