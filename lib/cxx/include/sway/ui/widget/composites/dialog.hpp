#ifndef SWAY_UI_WIDGET_DIALOG_HPP
#define SWAY_UI_WIDGET_DIALOG_HPP

#include <sway/ui/_stdafx.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/_typedefs.hpp>
#include <sway/ui/widget/composites/backdrop.hpp>
#include <sway/ui/widget/composites/draggable.hpp>
#include <sway/ui/widget/composites/popup.hpp>
#include <sway/ui/widget/typedefs.hpp>

namespace sway::ui {

class Dialog : public Popup {
public:
#pragma region "Pointer aliases"
  /** \~english @name Pointer aliases */ /** \~russian @name Типы указателей */

  using SharedPtr_t = DialogSharedPtr_t;

  /** @{ */
#pragma endregion

#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  Dialog(BuilderPtr_t builder);

  virtual ~Dialog();

  /** @} */
#pragma endregion

#pragma region "Overridden Widget methods"

  MTHD_OVERRIDE(void update());

  MTHD_OVERRIDE(void repaint(PainterSharedPtr_t painter));

#pragma endregion

  void setBackdrop();

  void setDragability(bool draggable);

  void show();

  void hide();

private:
  core::Subscribable::Subscriber_t subscriber_;

  BackdropSharedPtr_t backdrop_;
  DraggableSharedPtr_t draghead_;

  bool draggable_;
  bool resizable_;
};

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGET_DIALOG_HPP
