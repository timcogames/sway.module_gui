#ifndef SWAY_UI_LAYOUT_LINEARLAYOUT_HPP
#define SWAY_UI_LAYOUT_LINEARLAYOUT_HPP

#include <sway/core.hpp>
#include <sway/ui/layout/_typedefs.hpp>
#include <sway/ui/layout/layout.hpp>
#include <sway/ui/orientations.hpp>
#include <sway/ui/painter.hpp>

#include <memory>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class LinearLayout : public Layout {
public:
#pragma region "Static methods"

  /**
   * @name creators
   * @{
   */

  static auto create(BuilderTypedefs::Ptr_t builder, Orientation orien = Orientation::VERT)
      -> LinearLayoutTypedefs::SharedPtr_t;

  /**
   * end of creators group
   * @}
   */

#pragma endregion

#pragma region "Ctors/Dtor"

  LinearLayout(BuilderTypedefs::Ptr_t builder, Orientation orien);

  DTOR_VIRTUAL_DEFAULT(LinearLayout);

#pragma endregion

  void build();

  MTHD_OVERRIDE(void recursiveUpdateItemOffset(const math::point2f_t offset));
};

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_LAYOUT_LINEARLAYOUT_HPP
