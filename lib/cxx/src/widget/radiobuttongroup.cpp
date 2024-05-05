#include <sway/ui/builder.hpp>
#include <sway/ui/widget/radiobutton.hpp>
#include <sway/ui/widget/radiobuttongroup.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

RadioButtonGroup::RadioButtonGroup(Builder *builder, LinearLayoutOrientation orientation)
    : LinearLayout(builder, orientation)
    , selected_(std::nullopt) {
  this->subscribe(this, "NodeAdded", EVENT_HANDLER(RadioButtonGroup, handleAddNode));
}

void RadioButtonGroup::deselect() {
  for (auto const &child : this->getChildNodes()) {
    std::static_pointer_cast<RadioButton>(child)->setChecked(false);
  }
}

void RadioButtonGroup::handleAddNode(core::foundation::Event *evt) {
  auto self = sharedFrom<RadioButtonGroup>(this);

  auto parentNodeIdx = self->getNodeIdx();
  auto childNodeIdx = static_cast<core::container::NodeEventData *>(evt->data())->nodeidx;

  auto childOpt = self->getChildAt(childNodeIdx.getIdxAt(
      core::container::NodeIdx::getMatchDepth(parentNodeIdx.getChain(), childNodeIdx.getChain())));
  if (!childOpt.has_value()) {
    return;
  }

  auto child = std::static_pointer_cast<RadioButton>(childOpt.value());
  if (selected_.has_value() && child->isChecked()) {
    std::cout << "RadioButton is checked ignore" << std::endl;
  }

  child->subscribe(child.get(), "MouseClicked", EVENT_HANDLER(RadioButtonGroup, handleClickedEvent));
}

void RadioButtonGroup::handleClickedEvent(core::foundation::Event *evt) {
  for (auto const &child : this->getChildNodes()) {
    auto radioBtn = std::static_pointer_cast<RadioButton>(child);
    auto radioBtnIdx = radioBtn->getNodeIdx();
    auto radioBtnEvtdata = static_cast<ui::widget::MouseClickEventData *>(evt->data());

    radioBtn->setChecked(false);

    if (radioBtnIdx.equal(radioBtnEvtdata->nodeidx)) {
      radioBtn->setChecked(true);
      selected_ = radioBtn;

      auto *evtdata = new RadioButtonGroupChangeEventData();
      evtdata->nodeidx = selected_.value()->getNodeIdx();
      emit(EVT_CHANGED, new RadioButtonGroupChangedEvent(0, std::move(evtdata)),
          [&](core::foundation::EventHandler *) { return true; });
    }
  }
}

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)
