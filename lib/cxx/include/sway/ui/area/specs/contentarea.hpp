#ifndef SWAY_UI_AREA_CONTENTAREA_HPP
#define SWAY_UI_AREA_CONTENTAREA_HPP

#include <sway/ui/_stdafx.hpp>
#include <sway/ui/area/_typedefs.hpp>
#include <sway/ui/area/area.hpp>
#include <sway/ui/area/areatypes.hpp>

namespace sway::ui {

class ContentArea : public Area {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  ContentArea(const math::size2f_t &size = math::size2f_zero);

  virtual ~ContentArea() = default;

  /** @} */
#pragma endregion

#pragma region "Overridden Area methods"

  MTHD_OVERRIDE(auto getType() const -> AreaType);

#pragma endregion

  void setSize(const math::size2f_t &size);

  [[nodiscard]] auto getSize() const -> math::size2f_t;

  friend auto operator<<(std::ostream &out, const ContentAreaTypedefs::SharedPtr_t &area) -> std::ostream & {
    const auto size = area->getSize();
    return out << std::fixed << std::setprecision(3) << "{"
               << "w:" << size.getW() << ", "
               << "h:" << size.getH() << "}";
  }

private:
  math::size2f_t size_;
};

}  // namespace sway::ui

#endif  // SWAY_UI_AREA_CONTENTAREA_HPP
