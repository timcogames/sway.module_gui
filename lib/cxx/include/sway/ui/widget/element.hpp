#ifndef SWAY_UI_WIDGETS_ELEMENT_HPP
#define SWAY_UI_WIDGETS_ELEMENT_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ui/widget/elementareaholder.hpp>
#include <sway/ui/widget/elementpositions.hpp>
#include <sway/ui/widget/typedefs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

struct ElementOffset {
  math::point2f_t original;
  math::point2f_t computed;
  bool dirty;

  ElementOffset()
      : original(math::point2f_zero)
      , computed(math::point2f_zero)
      , dirty(false) {}

  void markAsDirty() { dirty = true; }
};

class Element : public core::container::Node {
  DECLARE_CLASS_POINTER_ALIASES(Element)

public:
#pragma region "Ctors/Dtor"

  Element();

  ~Element() = default;

#pragma endregion

#pragma region "Getters/Setters Position"

  void setPosition(ElementPosition pos);

  [[nodiscard]]
  auto getPosition() const -> ElementPosition;

#pragma endregion

#pragma region "Getters/Setters Offset"

  void setOffset(const math::point2f_t &pnt);

  void setOffset(f32_t x, f32_t y);

  auto getOffset() -> ElementOffset &;

#pragma endregion

  void updateOffset();

  void recursiveUpdate(Element::SharedPtr_t elem);

  [[nodiscard]]
  auto getAreaHolder() const -> ElementAreaHolder;

  [[nodiscard]]
  auto getInnerSize() const -> math::size2f_t;

  [[nodiscard]]
  auto getOuterSize() const -> math::size2f_t;

  [[nodiscard]]
  auto getOuterSizeWithMargin() const -> math::size2f_t;

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
