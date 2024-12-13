#ifndef SWAY_UI_WIDGETS_ELEMENT_HPP
#define SWAY_UI_WIDGETS_ELEMENT_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ui/widget/_typedefs.hpp>
#include <sway/ui/widget/elementareaholder.hpp>
#include <sway/ui/widget/elementoffset.hpp>
#include <sway/ui/widget/elementpositions.hpp>
#include <sway/ui/widget/typedefs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class Element : public core::container::Node {
  DECLARE_PTR_ALIASES(Element)

public:
#pragma region "Ctors/Dtor"

  Element();

  DTOR_DEFAULT(Element);

#pragma endregion

#pragma region "Getters/Setters Position"

  void setPosition(ElementPosition pos);

  [[nodiscard]] auto getPosition() const -> ElementPosition;

#pragma endregion

#pragma region "Getters/Setters Offset"

  /**
   * \~russian @brief Устанавливает оригинальное положение.
   * @param[in] pnt Новое оригинальное положение.
   * @sa setOffset(f32_t, f32_t)
   */
  void setOffset(const math::point2f_t &pnt);

  /**
   * \~russian @brief Устанавливает оригинальное положение.
   * @param[in] x Значение координаты по оси X.
   * @param[in] y Значение координаты по оси Y.
   * @sa setOffset(const math::point2f_t &)
   */
  void setOffset(f32_t x, f32_t y);

  auto getOffset() -> ElementOffset &;

#pragma endregion

  void updateOffset(Element::SharedPtr_t prev);

  void recursiveUpdate(Element::SharedPtr_t lhs, Element::SharedPtr_t rhs);

  [[nodiscard]] auto getAreaHolder() const -> ElementAreaHolder;

  [[nodiscard]] auto getInnerSize() const -> math::size2f_t;

  [[nodiscard]] auto getOuterSize() const -> math::size2f_t;

  [[nodiscard]] auto getOuterSizeWithMargin() const -> math::size2f_t;

  template <typename TYPE>
  auto cast(Node::SharedPtr_t ptr) -> std::shared_ptr<TYPE> {
    return std::static_pointer_cast<TYPE>(ptr);
  }

  template <typename TYPE>
  auto cast(std::optional<Node::SharedPtr_t> ptr) -> std::shared_ptr<TYPE> {
    return std::static_pointer_cast<TYPE>(ptr.value());
  }

  template <typename TYPE>
  auto getChild(const core::container::NodeIdx &idx) -> std::shared_ptr<TYPE> {
    return cast<TYPE>(getChildNode(idx));
  }

  void handleAddNode(core::foundation::Event::Ptr_t evt);

protected:
  math::Alignment alignment_;

private:
  ElementAreaHolder holder_;
  ElementPosition position_;
  ElementOffset offset_;
};

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGETS_ELEMENT_HPP
