#ifndef SWAY_UI_WIDGETS_AREAS_CONTENTAREA_HPP
#define SWAY_UI_WIDGETS_AREAS_CONTENTAREA_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ui/widget/area.hpp>
#include <sway/ui/widget/areatypes.hpp>
#include <sway/ui/widget/typedefs.hpp>

#include <array>
#include <iostream>  // std::ostream
#include <memory>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class ContentArea : public Area {
  DECLARE_PTR_ALIASES(ContentArea)

public:
#pragma region "Ctors/Dtor"

  ContentArea(const math::size2f_t &size = math::size2f_zero);

  DTOR_VIRTUAL_DEFAULT(ContentArea);

#pragma endregion

#pragma region "Overridden Area methods"

  MTHD_OVERRIDE(auto type() const -> AreaType);

#pragma endregion

  void setSize(const math::size2f_t &size);

  [[nodiscard]] auto getSize() const -> math::size2f_t;

  friend auto operator<<(std::ostream &out, const ContentArea::SharedPtr_t &area) -> std::ostream & {
    const auto size = area->getSize();
    return out << std::fixed << std::setprecision(3) << "{"
               << "w:" << size.getW() << ", "
               << "h:" << size.getH() << "}";
  }

private:
  math::size2f_t size_;
};

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGETS_AREAS_CONTENTAREA_HPP
