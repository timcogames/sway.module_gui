#ifndef SWAY_UI_WIDGET_DROPTAGET_HPP
#define SWAY_UI_WIDGET_DROPTAGET_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/typedefs.hpp>
#include <sway/ui/widget/widget.hpp>

#include <memory>
#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class DropSource {};

class DropTarget : public Widget {
  DECLARE_CLASS_POINTER_ALIASES(DropTarget)

public:
#pragma region "Ctors/Dtor"

  DropTarget(BuilderPtr_t builder);

  virtual ~DropTarget() = default;

#pragma endregion

#pragma region "Override Widget methods"

  MTHD_OVERRIDE(void update());

  MTHD_OVERRIDE(void repaint(Painter::SharedPtr_t painter));

#pragma endregion

  void onDragEnter();

  void onDragOver();

  auto onDrop() -> bool;

  void onDragLeave();

private:
  core::evts::EventBus::Subscriber_t subscriber_;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_DROPTAGET_HPP
