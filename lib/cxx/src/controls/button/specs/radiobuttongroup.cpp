#include <sway/ui/builder.hpp>
#include <sway/ui/controls/button/specs/radiobutton.hpp>
#include <sway/ui/controls/button/specs/radiobuttongroup.hpp>
#include <sway/ui/controls/button/specs/radiobuttongroupchangeeventdata.hpp>

namespace sway::ui {

RadioButtonGroup::RadioButtonGroup(BuilderPtr_t builder, Orientation orien)
    : LinearLayout(builder, orien)
    , selected_(std::nullopt) {
  this->subscribe(this, "NodeAdded", EVENT_HANDLER(RadioButtonGroup, handleAddNode));
}

void RadioButtonGroup::deselect() {
  for (auto const &child : this->getChildNodes()) {
    std::static_pointer_cast<RadioButton>(child)->setChecked(false);
  }
}

auto RadioButtonGroup::handleAddNode(const core::EventTypedefs::UniquePtr_t &evt) -> bool {
  auto self = getSharedFrom<RadioButtonGroup>(this);

  auto parentNodeIdx = self->getNodeIndex();
  auto childNodeIdx = static_cast<core::NodeEventData *>(evt->getData())->nodeidx;

  auto childOpt = self->getChildAt(
      childNodeIdx.getIndexAt(core::NodeIndex::getMatchDepth(parentNodeIdx.getChain(), childNodeIdx.getChain())));
  if (!childOpt.has_value()) {
    return false;
  }

  auto child = std::static_pointer_cast<RadioButton>(childOpt.value());
  if (selected_.has_value() && child->isChecked()) {
    std::cout << "RadioButton is checked ignore" << std::endl;
  }

  child->subscribe(child.get(), "MouseClicked", EVENT_HANDLER(RadioButtonGroup, handleClickedEvent));
  return true;
}

auto RadioButtonGroup::handleClickedEvent(const core::EventTypedefs::UniquePtr_t &evt) -> bool {
  for (auto const &child : this->getChildNodes()) {
    auto radioBtn = std::static_pointer_cast<RadioButton>(child);
    auto radioBtnIdx = radioBtn->getNodeIndex();
    auto radioBtnEvtData = static_cast<MouseClickEventData *>(evt->getData());

    radioBtn->setChecked(false);

    if (radioBtnIdx.equal(radioBtnEvtData->nodeidx)) {
      radioBtn->setChecked(true);
      selected_ = radioBtn;

      auto *evtdata = new RadioButtonGroupChangeEventData();
      evtdata->nodeidx = selected_.value()->getNodeIndex();
      emit(EVT_CHANGED, std::make_unique<RadioButtonGroupChangedEvent>(0, std::move(evtdata)),
          [&](core::EventHandler *) { return true; });
    }
  }

  return true;
}

}  // namespace sway::ui
