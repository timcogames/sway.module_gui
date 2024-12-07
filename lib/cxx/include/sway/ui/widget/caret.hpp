#ifndef SWAY_UI_WIDGETS_CARET_HPP
#define SWAY_UI_WIDGETS_CARET_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ui/widget/caretselectionrange.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

DECLARE_ENUM(TextModeType, VIEW, EDIT, EXPR)

struct Caret {
  math::rect4f_t rect;  ///< Прямоугольник курсора (позиция, размер).
  CaretSelectionRange range;  ///< Диапазон выделенного текста.
  bool visibled;  ///< Видимость курсора.
};

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGETS_CARET_HPP
