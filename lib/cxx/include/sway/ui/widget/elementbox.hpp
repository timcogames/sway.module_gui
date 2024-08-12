#ifndef SWAY_UI_WIDGET_ELEMENTBOX_HPP
#define SWAY_UI_WIDGET_ELEMENTBOX_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ui/widget/elementboxarea.hpp>
#include <sway/ui/widget/elementboxareatypes.hpp>

#include <array>
#include <optional>
#include <utility>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(widget)

#define NUM_AREAS 3  // MARGIN, BORDER, PADDING
#define NUM_EDGES 4

class ElementBox {
public:
#pragma region "Ctors/Dtor"

  ElementBox(const math::sizef_t &content)
      : content_(std::move(content)) {}

  ~ElementBox() = default;

#pragma endregion

  [[nodiscard]]
  auto getArea(ElementBoxAreaType type) const -> std::optional<ElementBoxArea> {
    std::optional<ElementBoxArea> area = std::nullopt;
    for (const auto item : areas_) {
      if (item.has_value() && item.value().type == type) {
        area = item;
      }
    }

    return area;
  }

  [[nodiscard]]
  auto getPosition(ElementBoxAreaType type) const -> math::vec2f_t {
    auto result = math::vec2f_zero;

    auto mgn = this->getArea(ElementBoxAreaType::MARGIN);
    if (!mgn.has_value()) {
    } else {
      result = math::vec2f_t(-std::get<core::detail::toBase(math::RectEdge::IDX_L)>(mgn.value().edges),
          -std::get<core::detail::toBase(math::RectEdge::IDX_T)>(mgn.value().edges));
    }

    auto brd = this->getArea(ElementBoxAreaType::BORDER);
    if (!brd.has_value()) {
    } else {
      result = math::vec2f_t(result.getX() + std::get<core::detail::toBase(math::RectEdge::IDX_L)>(brd.value().edges),
          result.getY() + std::get<core::detail::toBase(math::RectEdge::IDX_T)>(brd.value().edges));
    }

    auto pad = this->getArea(ElementBoxAreaType::PADDING);
    if (!pad.has_value()) {
    } else {
      result = math::vec2f_t(result.getX() + std::get<core::detail::toBase(math::RectEdge::IDX_L)>(pad.value().edges),
          result.getY() + std::get<core::detail::toBase(math::RectEdge::IDX_T)>(pad.value().edges));
    }

    return result;
  }

private:
  math::sizef_t content_;
  std::array<std::optional<ElementBoxArea>, NUM_AREAS> areas_;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_ELEMENTBOX_HPP
