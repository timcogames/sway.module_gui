#ifndef SWAY_UI_WIDGET_POPUP_HPP
#define SWAY_UI_WIDGET_POPUP_HPP

#include <sway/ui/_stdafx.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/draggable.hpp>
#include <sway/ui/widget/typedefs.hpp>

namespace sway::ui {

class Popup : public Widget {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  Popup(BuilderPtr_t builder);

  virtual ~Popup();

  /** @} */
#pragma endregion

#pragma region "Overridden Widget methods"

  MTHD_OVERRIDE(void update());

  MTHD_OVERRIDE(void repaint(PainterSharedPtr_t painter));

#pragma endregion

private:
  core::Subscribable::Subscriber_t subscriber_;
};

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGET_POPUP_HPP
