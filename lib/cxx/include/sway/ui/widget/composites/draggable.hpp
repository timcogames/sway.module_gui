#ifndef SWAY_UI_WIDGET_DRAGSOURCE_HPP
#define SWAY_UI_WIDGET_DRAGSOURCE_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/widget.hpp>

#include <memory>
#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class Draggable : public Widget {
public:
  using Ptr_t = Draggable *;
  using SharedPtr_t = std::shared_ptr<Draggable>;

#pragma region "Ctors/Dtor"

  Draggable(BuilderPtr_t builder);

  virtual ~Draggable();

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
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_DRAGSOURCE_HPP
