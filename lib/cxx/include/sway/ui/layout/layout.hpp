#ifndef SWAY_UI_LAYOUT_HPP
#define SWAY_UI_LAYOUT_HPP

#include <sway/core.hpp>
#include <sway/ui/layout/_typedefs.hpp>
#include <sway/ui/orientable.hpp>
#include <sway/ui/orientations.hpp>
#include <sway/ui/widget/widget.hpp>

namespace sway::ui {

class Layout : public LayoutItem, public Orientable {
public:
#pragma region "Static methods"

  /**
   * \~english @brief Returns the size of the layout cell.
   * @param[in] elem Pointer to the layout element.
   *
   * \~russian @brief Возвращает размер ячейки макета.
   * @param[in] elem Указатель на элемент макета.
   *
   * @return math::size2f_t
   */
  static auto getCellSize(ElementTypedefs::Ptr_t elem) -> math::size2f_t;

#pragma endregion

#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  Layout(BuilderTypedefs::Ptr_t builder, Orientation orien);

  virtual ~Layout() = default;

  /** @} */
#pragma endregion

  MTHD_OVERRIDE(auto getBarrierType() const -> BarrierType) { return BarrierType::LAYOUT; }
};

}  // namespace sway::ui

#endif  // SWAY_UI_LAYOUT_HPP
