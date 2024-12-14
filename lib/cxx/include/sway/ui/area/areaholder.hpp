#ifndef SWAY_UI_AREA_AREAHOLDER_HPP
#define SWAY_UI_AREA_AREAHOLDER_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ui/area/_typedefs.hpp>
#include <sway/ui/area/area.hpp>
#include <sway/ui/area/areatypes.hpp>

#include <array>
#include <memory>
#include <optional>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class AreaHolder : public AreaTypedefs::Container_t {
public:
#pragma region "Ctors/Dtor"

  AreaHolder();

  DTOR_DEFAULT(AreaHolder);

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

NS_END()  // namespace ui
NS_END()  // namespace sway

#include <sway/ui/area/areaholder.inl>

#endif  // SWAY_UI_AREA_AREAHOLDER_HPP
