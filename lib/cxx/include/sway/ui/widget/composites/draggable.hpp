#ifndef SWAY_UI_WIDGET_DRAGSOURCE_HPP
#define SWAY_UI_WIDGET_DRAGSOURCE_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/typedefs.hpp>
#include <sway/ui/widget/widget.hpp>

#include <memory>
#include <string>

NS_BEGIN_SWAY()
NS_BEGIN(ui)
NS_BEGIN(widget)

class Draggable : public Widget {
  DECLARE_PTR_ALIASES(Draggable)

public:
#pragma region "Ctors/Dtor"

  Draggable(BuilderPtr_t builder);

  DTOR_VIRTUAL(Draggable);

#pragma endregion

#pragma region "Override Widget methods"

  MTHD_OVERRIDE(void update());

  MTHD_OVERRIDE(void repaint(Painter::SharedPtr_t painter));

#pragma endregion

  void handleMouseClickedEvent(core::foundation::Event *evt);

private:
  core::evts::EventBus::Subscriber_t subscriber_;
  bool hovering_;
  bool dragging_;

  math::point2f_t mouseDownPosition_ = math::point2f_zero;
  math::point2f_t mouseDownOffset_ = math::point2f_zero;
  // math::bounds2f_t mouseDownBounds_;
  bool mouseIsDown_ = false;
};

NS_END()  // namespace widget
NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGET_DRAGSOURCE_HPP
