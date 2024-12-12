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

NS_BEGIN_SWAY()
NS_BEGIN(ui)
NS_BEGIN(widget)

class Dialog : public Popup {
  DECLARE_PTR_ALIASES(Dialog)

public:
#pragma region "Ctors/Dtor"

  Dialog(BuilderTypedefs::Ptr_t builder);

  DTOR_VIRTUAL(Dialog);

#pragma endregion

#pragma region "Overridden Widget methods"

  MTHD_OVERRIDE(void update());

  MTHD_OVERRIDE(void repaint(PainterTypedefs::SharedPtr_t painter));

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

NS_END()  // namespace widget
NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGET_DIALOG_HPP
