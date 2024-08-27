#include <sway/core.hpp>
#include <sway/ui/builder.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/dialog.hpp>

#include <memory>
#include <string>
#include <unordered_map>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

Dialog::Dialog(BuilderPtr_t builder)
    : Popup(builder) {
  dragWidget_ = std::make_shared<Draggable>(this->builder_);
  this->addChildNode(dragWidget_);
}

Dialog::~Dialog() {}

void Dialog::setDragability(bool draggable) { draggable_ = draggable; }

void Dialog::show() {}

void Dialog::hide() {}

void Dialog::update() {}

void Dialog::repaint(Painter::SharedPtr_t painter) {
  auto offset = this->getOffset(ElementPosition::RELATIVE);

  dragWidget_->setAlignment(math::Alignment::CENTER);
  dragWidget_->setOffset({0.0F, 0.0F});
  dragWidget_->setSize({800.0F, 600.0F});
  dragWidget_->setBackgroundColor(COL4F_BEIGE);

  Popup::repaint(painter);
}

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
