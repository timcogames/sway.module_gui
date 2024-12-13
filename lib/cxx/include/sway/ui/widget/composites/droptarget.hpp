#ifndef SWAY_UI_WIDGET_DROPTAGET_HPP
#define SWAY_UI_WIDGET_DROPTAGET_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/typedefs.hpp>
#include <sway/ui/widget/widget.hpp>

#include <memory>
#include <string>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class DropSource {};

class DropTarget : public Widget {
  DECLARE_PTR_ALIASES(DropTarget)

public:
#pragma region "Ctors/Dtor"

  DropTarget(BuilderTypedefs::Ptr_t builder);

  DTOR_VIRTUAL_DEFAULT(DropTarget);

#pragma endregion

#pragma region "Overridden Widget methods"

  MTHD_OVERRIDE(void update());

  MTHD_OVERRIDE(void repaint(PainterTypedefs::SharedPtr_t painter));

#pragma endregion

  void onDragEnter();

  void onDragOver();

  auto onDrop() -> bool;

  void onDragLeave();

private:
  core::evts::EventBus::Subscriber_t subscriber_;
};

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGET_DROPTAGET_HPP
