#ifndef SWAY_UI_WIDGETS_CARET_HPP
#define SWAY_UI_WIDGETS_CARET_HPP

#include <sway/ui/_stdafx.hpp>
#include <sway/ui/widget/caretselectionrange.hpp>

namespace sway::ui {

DECLARE_ENUM(TextModeType, VIEW, EDIT, EXPR)

struct Caret {
  math::rect4f_t rect; /*< Прямоугольник курсора (позиция, размер). */
  CaretSelectionRange range; /*< Диапазон выделенного текста. */
  bool visibled; /*< Видимость курсора. */
};

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGETS_CARET_HPP
