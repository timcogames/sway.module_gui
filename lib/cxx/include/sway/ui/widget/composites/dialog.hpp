#ifndef SWAY_UI_WIDGET_DIALOG_HPP
#define SWAY_UI_WIDGET_DIALOG_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/draggable.hpp>
#include <sway/ui/widget/composites/overlay.hpp>
#include <sway/ui/widget/composites/popup.hpp>

#include <memory>
#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class Dialog : public Popup {
public:
  using Ptr_t = Dialog *;
  using SharedPtr_t = std::shared_ptr<Dialog>;

#pragma region "Ctors/Dtor"

  Dialog(BuilderPtr_t builder);

  virtual ~Dialog();

#pragma endregion

#pragma region "Override Widget methods"

  MTHD_OVERRIDE(void update());

  MTHD_OVERRIDE(void repaint(Painter::SharedPtr_t painter));

#pragma endregion

  void setDragability(bool draggable);

  void show();

  void hide();

private:
  core::evts::EventBus::Subscriber_t subscriber_;

  Overlay::SharedPtr_t overlayWidget_;
  Draggable::SharedPtr_t dragWidget_;

  bool draggable_;
  bool resizable_;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_DIALOG_HPP
