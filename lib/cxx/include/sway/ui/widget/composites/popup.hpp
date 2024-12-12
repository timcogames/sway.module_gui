#ifndef SWAY_UI_WIDGET_POPUP_HPP
#define SWAY_UI_WIDGET_POPUP_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/composites/draggable.hpp>
#include <sway/ui/widget/typedefs.hpp>

#include <memory>
#include <string>

NS_BEGIN_SWAY()
NS_BEGIN(ui)
NS_BEGIN(widget)

class Popup : public Widget {
  DECLARE_PTR_ALIASES(Popup)

public:
#pragma region "Ctors/Dtor"

  Popup(BuilderTypedefs::Ptr_t builder);

  DTOR_VIRTUAL(Popup);

#pragma endregion

#pragma region "Overridden Widget methods"

  MTHD_OVERRIDE(void update());

  MTHD_OVERRIDE(void repaint(PainterTypedefs::SharedPtr_t painter));

#pragma endregion

private:
  core::evts::EventBus::Subscriber_t subscriber_;
};

NS_END()  // namespace widget
NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGET_POPUP_HPP
