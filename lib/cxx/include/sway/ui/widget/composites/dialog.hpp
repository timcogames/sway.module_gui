#ifndef SWAY_UI_WIDGET_DIALOG_HPP
#define SWAY_UI_WIDGET_DIALOG_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/backdrop.hpp>
#include <sway/ui/widget/composites/draggable.hpp>
#include <sway/ui/widget/composites/popup.hpp>
#include <sway/ui/widget/typedefs.hpp>

#include <memory>
#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class Dialog : public Popup {
  DECLARE_CLASS_POINTER_ALIASES(Dialog)

public:
#pragma region "Ctors/Dtor"

  Dialog(BuilderPtr_t builder);

  virtual ~Dialog();

#pragma endregion

#pragma region "Override Widget methods"

  MTHD_OVERRIDE(void update());

  MTHD_OVERRIDE(void repaint(Painter::SharedPtr_t painter));

#pragma endregion

  void setBackdrop();

  void setDragability(bool draggable);

  void show();

  void hide();

private:
  core::evts::EventBus::Subscriber_t subscriber_;

  Backdrop::SharedPtr_t backdrop_;
  Draggable::SharedPtr_t draghead_;

  bool draggable_;
  bool resizable_;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_DIALOG_HPP
