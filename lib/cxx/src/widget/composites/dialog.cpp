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
    : Popup(builder)
    , backdrop_(nullptr) {
  this->setPosition(ElementPosition::ABSOLUTE);

  dragHeader_ = std::make_shared<Draggable>(this->builder_);
  this->addChildNode(dragHeader_);
}

Dialog::~Dialog() {}

void Dialog::setBackdrop() {
  backdrop_ = std::make_shared<Backdrop>(this->builder_);
  this->getParentNode().value()->addChildNode(backdrop_);
}

void Dialog::setDragability(bool draggable) { draggable_ = draggable; }

void Dialog::show() {}

void Dialog::hide() {}

void Dialog::update() {}

void Dialog::repaint(Painter::SharedPtr_t painter) {
  auto offset = this->getOffset();

  if (backdrop_) {
    backdrop_->setOffset(0.0F, 0.0F);
    backdrop_->setSize(800.0F, 600.0F);
    backdrop_->setBackgroundColor(COL4F_BEIGE);
  }

  dragHeader_->setAlignment(math::Alignment::CENTER);
  dragHeader_->setOffset(0.0F, 0.0F);
  dragHeader_->setSize(800.0F, 20.0F);
  dragHeader_->setBackgroundColor(COL4F_GREEN);

  Popup::repaint(painter);
}

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
