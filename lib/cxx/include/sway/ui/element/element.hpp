#ifndef SWAY_UI_ELEMENT_HPP
#define SWAY_UI_ELEMENT_HPP

#include <sway/core.hpp>
#include <sway/core/container/nodeindexchain.hpp>
#include <sway/core/container/nodeutil.hpp>
#include <sway/math.hpp>
#include <sway/ois.hpp>
#include <sway/ui/area/areaholder.hpp>
#include <sway/ui/barriertypes.hpp>
#include <sway/ui/element/_typedefs.hpp>
#include <sway/ui/element/elementoffset.hpp>
#include <sway/ui/element/elementpositions.hpp>

namespace sway::ui {

class Element : public core::Node, public core::Visibleable {
  DECLARE_EVENT(EVT_POINTER_ENTER, PointerEnter)
  DECLARE_EVENT(EVT_POINTER_LEAVE, PointerLeave)
  DECLARE_EVENT(EVT_MOUSE_CLICKED, MouseClicked)

public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  Element();

  virtual ~Element() = default;

  /** @} */
#pragma endregion

#pragma region "Pure virtual methods"

  virtual void recursiveUpdateItemOffset(const math::point2f_t offset) = 0;

  virtual auto getBarrierType() const -> BarrierType = 0;

#pragma endregion

#pragma region "Getters/Setters Position"

  void setPosition(ElementPosition pos);

  [[nodiscard]] auto getPosition() const -> ElementPosition;

#pragma endregion

#pragma region "Getters/Setters Offset"

  /**
   * \~russian @brief Устанавливает оригинальное положение.
   * @param[in] pnt Новое оригинальное положение.
   *
   * @sa setOffset(f32_t, f32_t)
   */
  void setOffset(const math::point2f_t &pnt);

  /**
   * \~russian @brief Устанавливает оригинальное положение.
   * @param[in] x Значение координаты по оси X.
   * @param[in] y Значение координаты по оси Y.
   *
   * @sa setOffset(const math::point2f_t &)
   */
  void setOffset(f32_t x, f32_t y);

  auto getOffset() -> ElementOffset &;

#pragma endregion

  void updateOffset();

  [[nodiscard]] auto getAreaHolder() const -> AreaHolder;

  [[nodiscard]] auto getInnerSize() const -> math::size2f_t;

  [[nodiscard]] auto getOuterSize() const -> math::size2f_t;

  [[nodiscard]] auto getOuterSizeWithMargin() const -> math::size2f_t;

  auto handleAddNode(const core::EventTypedefs::UniquePtr_t &evt) -> bool;

#pragma region "Getters/Setters Size"

  void setSize(const math::size2f_t &size);

  void setSize(f32_t wdt, f32_t hgt);

  [[nodiscard]] auto getSize() const -> math::size2f_t;

#pragma endregion

  auto getChildAtPoint(const math::point2f_t &point) -> ElementTypedefs::Ptr_t;

  void setEventFilter(core::EventHandlerTypedefs::Ptr_t handler) { eventFilter_ = handler; }

  void setMouseFilter(ois::MouseFilter filter) { mouseFilter_ = filter; }

  [[nodiscard]] auto getMouseFilter() const -> ois::MouseFilter { return mouseFilter_; }

  void onCursorPointerEnter();

  void onCursorPointerLeave();

  void onMouseClick(u32_t state);

protected:
  math::Alignment alignment_;

private:
  AreaHolder holder_;
  ElementPosition position_;
  ElementOffset offset_;

  core::EventHandlerTypedefs::Ptr_t eventFilter_;
  ois::MouseFilter mouseFilter_;
  bool containsPointer_;
};

}  // namespace sway::ui

#endif  // SWAY_UI_ELEMENT_HPP
