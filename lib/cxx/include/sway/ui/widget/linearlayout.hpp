#ifndef SWAY_UI_WIDGET_LINEARLAYOUT_HPP
#define SWAY_UI_WIDGET_LINEARLAYOUT_HPP

#include <sway/core.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/layout.hpp>
#include <sway/ui/widget/layoutorientations.hpp>

#include <memory>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

class LinearLayout : public Layout {
public:
  using Ptr_t = LinearLayout *;
  using SharedPtr_t = std::shared_ptr<LinearLayout>;

#pragma region "Ctors/Dtor"

  LinearLayout(BuilderPtr_t builder, LayoutOrientation orien);

  virtual ~LinearLayout() = default;

#pragma endregion

  void build();
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_LINEARLAYOUT_HPP
