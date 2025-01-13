#ifndef SWAY_UI_WIDGET_BACKDROP_HPP
#define SWAY_UI_WIDGET_BACKDROP_HPP

#include <sway/ui/_stdafx.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/typedefs.hpp>
#include <sway/ui/widget/widget.hpp>

namespace sway::ui {

// pseudo-element
class Backdrop : public Widget {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  Backdrop(BuilderPtr_t builder);

  virtual ~Backdrop() = default;

  /** @} */
#pragma endregion

#pragma region "Overridden Widget methods"

  MTHD_OVERRIDE(void update());

  MTHD_OVERRIDE(void repaint(PainterSharedPtr_t painter));

#pragma endregion
};

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGET_BACKDROP_HPP
