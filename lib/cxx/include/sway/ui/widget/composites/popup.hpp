#ifndef SWAY_UI_WIDGET_POPUP_HPP
#define SWAY_UI_WIDGET_POPUP_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/draggable.hpp>
#include <sway/ui/widget/typedefs.hpp>

#include <memory>
#include <string>

namespace sway::ui {

class Popup : public Widget {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  Popup(BuilderTypedefs::Ptr_t builder);

  virtual ~Popup();

  /** @} */
#pragma endregion

#pragma region "Overridden Widget methods"

  MTHD_OVERRIDE(void update());

  MTHD_OVERRIDE(void repaint(PainterTypedefs::SharedPtr_t painter));

#pragma endregion

private:
  core::Subscribable::Subscriber_t subscriber_;
};

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGET_POPUP_HPP
