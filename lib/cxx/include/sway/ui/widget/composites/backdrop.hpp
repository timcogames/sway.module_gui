#ifndef SWAY_UI_WIDGET_BACKDROP_HPP
#define SWAY_UI_WIDGET_BACKDROP_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/typedefs.hpp>
#include <sway/ui/widget/widget.hpp>

#include <memory>
#include <string>

namespace sway::ui {

// pseudo-element
class Backdrop : public Widget {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  Backdrop(BuilderTypedefs::Ptr_t builder);

  virtual ~Backdrop() = default;

  /** @} */
#pragma endregion

#pragma region "Overridden Widget methods"

  MTHD_OVERRIDE(void update());

  MTHD_OVERRIDE(void repaint(PainterTypedefs::SharedPtr_t painter));

#pragma endregion
};

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGET_BACKDROP_HPP
