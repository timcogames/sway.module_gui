#include <sway/core.hpp>
#include <sway/ui/builder.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/dialog.hpp>

#include <memory>
#include <string>
#include <unordered_map>

namespace sway::ui {

Dialog::Dialog(BuilderPtr_t builder)
    : Popup(builder)
    , backdrop_(nullptr)
    , draghead_(nullptr) {
  this->setPosition(ElementPosition::ABSOLUTE);
}

Dialog::~Dialog() {}

void Dialog::setBackdrop() {
  backdrop_ = std::make_shared<Backdrop>(this->builder_);
  this->getParentNode().value()->addChildNode(backdrop_);
}

void Dialog::setDragability(bool val) {
  draghead_ = std::make_shared<Draggable>(this->builder_);
  this->addChildNode(draghead_);

  draggable_ = val;
}

void Dialog::show() {}

void Dialog::hide() {}

void Dialog::update() {}

void Dialog::repaint(PainterSharedPtr_t painter) {
  auto offset = this->getOffset().computed;
  auto contentSize = this->getAreaHolder().getContentSize();

  draghead_->setSize(contentSize.getW(), 20.0F);
  draghead_->setBackgroundColor(COL4F_GREEN);

  backdrop_->setSize(painter->getScreenSize());
  // backdrop_->setBackgroundColor(COL4F_BEIGE);
  backdrop_->setBackgroundColor(math::col4f_t(0.81F, 0.75F, 0.68F, 0.5F));

  Popup::repaint(painter);
}

}  // namespace sway::ui
