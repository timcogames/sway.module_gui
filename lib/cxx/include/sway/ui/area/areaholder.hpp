#ifndef SWAY_UI_AREA_AREAHOLDER_HPP
#define SWAY_UI_AREA_AREAHOLDER_HPP

#include <sway/ui/_stdafx.hpp>
#include <sway/ui/area/_typedefs.hpp>
#include <sway/ui/area/area.hpp>
#include <sway/ui/area/areatypes.hpp>

namespace sway::ui {

class AreaHolder : public AreaTypedefs::Container_t {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  AreaHolder();

  ~AreaHolder() = default;

  /** @} */
#pragma endregion

  auto getAreaIndex(AreaType type) const -> i32_t;

  template <AreaType TYPE>
  auto getAreaIndex() const -> i32_t;

  auto getArea(AreaType type) const -> AreaTypedefs::OptionalSharedPtr_t;

  template <AreaType TYPE, typename OUT = OutputAreaType_t<TYPE>>
  auto getArea() const -> std::optional<std::shared_ptr<OUT>>;

  template <AreaType TYPE, math::RectEdge::Enum EDGE>
  void setEdge(f32_t size);

  // template <math::RectEdge::Enum EDGE>
  // auto getEdge(AreaTypedefs::OptionalSharedPtr_t area) const -> f32_t;

  template <math::RectEdge::Enum EDGE>
  auto getEdge(AreaTypedefs::SharedPtr_t area) const -> f32_t;

  template <AreaType TYPE, math::RectEdge::Enum EDGE>
  auto getEdge() const -> f32_t;

  template <AreaType TYPE>
  auto getPosition() const -> math::vec2f_t;

  template <AreaType TYPE>
  auto getSize() const -> math::size2f_t;

  [[nodiscard]] auto getContentSize() const -> math::size2f_t;
};

}  // namespace sway::ui

#include <sway/ui/area/areaholder.inl>

#endif  // SWAY_UI_AREA_AREAHOLDER_HPP
