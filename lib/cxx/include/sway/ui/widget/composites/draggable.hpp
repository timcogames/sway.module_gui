#ifndef SWAY_UI_WIDGET_DRAGSOURCE_HPP
#define SWAY_UI_WIDGET_DRAGSOURCE_HPP

#include <sway/ui/_stdafx.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/typedefs.hpp>
#include <sway/ui/widget/widget.hpp>

namespace sway::ui {

class Draggable : public Widget {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  Draggable(BuilderPtr_t builder);

  virtual ~Draggable();

  /** @} */
#pragma endregion

#pragma region "Overridden Widget methods"

  MTHD_OVERRIDE(void update());

  MTHD_OVERRIDE(void repaint(PainterSharedPtr_t painter));

#pragma endregion

  bool handleMouseClickedEvent(const core::EventTypedefs::UniquePtr_t &evt);

private:
  core::Subscribable::Subscriber_t subscriber_;
  bool hovering_;
  bool dragging_;

  math::point2f_t mouseDownPosition_ = math::point2f_zero;
  math::point2f_t mouseDownOffset_ = math::point2f_zero;
  // math::bounds2f_t mouseDownBounds_;
  bool mouseIsDown_ = false;
};

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGET_DRAGSOURCE_HPP
