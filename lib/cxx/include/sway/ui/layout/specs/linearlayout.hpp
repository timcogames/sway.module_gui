#ifndef SWAY_UI_LINEARLAYOUT_HPP
#define SWAY_UI_LINEARLAYOUT_HPP

#include <sway/ui/_stdafx.hpp>
#include <sway/ui/layout/_typedefs.hpp>
#include <sway/ui/layout/layout.hpp>
#include <sway/ui/orientations.hpp>
#include <sway/ui/painter.hpp>

namespace sway::ui {

class LinearLayout : public Layout {
public:
#pragma region "Static methods"
  /** \~english @name Creators */ /** \~russian @name Создатели */
  /** @{ */

  static auto create(BuilderPtr_t builder, Orientation orien = Orientation::VERT) -> LinearLayoutSharedPtr_t;

  /** @} */
#pragma endregion

#pragma region "Pointer aliases"
  /** \~english @name Pointer aliases */ /** \~russian @name Типы указателей */
  /** @{ */

  using SharedPtr_t = LinearLayoutSharedPtr_t;

  /** @} */
#pragma endregion

#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  LinearLayout(BuilderPtr_t builder, Orientation orien);

  virtual ~LinearLayout() = default;

  /** @} */
#pragma endregion

  /**
   * \~english
   * @brief Sets the adjacent offset for each child element in the linear layout.
   * @details This method sets the adjacent offset for each child element in the linear layout. The adjacent offset is
   * used to calculate the position of each element in the layout.
   *
   * \~russian
   * @brief Устанавливает смещение дочернего соседа в линейном макете.
   * @details Этот метод устанавливает смещение дочернего соседа относительно предыдущего элемента в линейном макете.
   * Смещение соседа используется для вычисления позиции каждого элемента в макете.
   */
  void setOffsetAdjacentChild();

#pragma region "Overridden Layout > LayoutItem > Element methods"

  void recursiveUpdateItemOffset(const math::point2f_t offset) override;

#pragma endregion
};

}  // namespace sway::ui

#endif  // SWAY_UI_LINEARLAYOUT_HPP
