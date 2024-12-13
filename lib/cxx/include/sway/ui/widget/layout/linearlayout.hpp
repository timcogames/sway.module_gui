#ifndef SWAY_UI_WIDGET_LINEARLAYOUT_HPP
#define SWAY_UI_WIDGET_LINEARLAYOUT_HPP

#include <sway/core.hpp>
#include <sway/ui/orientations.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/layout/layout.hpp>

#include <memory>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class LinearLayout : public Layout {
public:
  using Ptr_t = LinearLayout *;
  using SharedPtr_t = std::shared_ptr<LinearLayout>;

#pragma region "Ctors/Dtor"

  LinearLayout(BuilderTypedefs::Ptr_t builder, Orientation orien);

  DTOR_VIRTUAL_DEFAULT(LinearLayout);

#pragma endregion

  void build();
};

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGET_LINEARLAYOUT_HPP
