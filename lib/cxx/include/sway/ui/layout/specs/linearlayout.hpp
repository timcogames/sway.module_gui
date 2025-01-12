#ifndef SWAY_UI_LINEARLAYOUT_HPP
#define SWAY_UI_LINEARLAYOUT_HPP

#include <sway/core.hpp>
#include <sway/ui/layout/_typedefs.hpp>
#include <sway/ui/layout/layout.hpp>
#include <sway/ui/orientations.hpp>
#include <sway/ui/painter.hpp>

#include <memory>

namespace sway::ui {

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

#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  LinearLayout(BuilderTypedefs::Ptr_t builder, Orientation orien);

  virtual ~LinearLayout() = default;

  /** @} */
#pragma endregion

  /**
   * \~english @brief Set the Adjacent object.
   * @details
   *   This method sets the adjacent offset for each child element
   *   in the linear layout. The adjacent offset is used to calculate
   *   the position of each element in the layout.
   *
   * \~russian @brief Устанавливает смещение соседа.
   * @details
   *   Этот метод устанавливает смещение соседа для каждого элемента
   *   в линейном макете. Смещение соседа используется для вычисления
   *   положения каждого элемента в макете.
   *
   * @see Layout::getCellSize()
   */
  void setAdjacent();

#pragma region "Overridden Layout > LayoutItem > Element methods"

  void recursiveUpdateItemOffset(const math::point2f_t offset) override;

#pragma endregion
};

}  // namespace sway::ui

#endif  // SWAY_UI_LINEARLAYOUT_HPP
