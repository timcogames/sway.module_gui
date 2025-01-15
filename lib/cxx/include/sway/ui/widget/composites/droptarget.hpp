#ifndef SWAY_UI_WIDGET_DROPTAGET_HPP
#define SWAY_UI_WIDGET_DROPTAGET_HPP

#include <sway/ui/_stdafx.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/_typedefs.hpp>
#include <sway/ui/widget/widget.hpp>

namespace sway::ui {

class DropSource {};

class DropTarget : public Widget {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  DropTarget(BuilderPtr_t builder);

  virtual ~DropTarget() = default;

  /** @} */
#pragma endregion

#pragma region "Overridden Widget methods"

  MTHD_OVERRIDE(void update());

  MTHD_OVERRIDE(void repaint(PainterSharedPtr_t painter));

#pragma endregion

  void onDragEnter();

  void onDragOver();

  auto onDrop() -> bool;

  void onDragLeave();

private:
  core::Subscribable::Subscriber_t subscriber_;
};

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGET_DROPTAGET_HPP
