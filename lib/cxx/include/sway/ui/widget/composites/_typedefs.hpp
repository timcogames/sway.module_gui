#ifndef SWAY_UI_WIDGET_COMPOSITES_TYPEDEFS_HPP
#define SWAY_UI_WIDGET_COMPOSITES_TYPEDEFS_HPP

#include <sway/ui/_stdafx.hpp>

namespace sway::ui {

class Menu;
class Dialog;

using MenuPtr_t = Menu *;
using MenuSharedPtr_t = std::shared_ptr<Menu>;

using DialogSharedPtr_t = std::shared_ptr<Dialog>;

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGET_COMPOSITES_TYPEDEFS_HPP
