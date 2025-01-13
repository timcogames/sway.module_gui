#ifndef SWAY_UI_TYPEDEFS_HPP
#define SWAY_UI_TYPEDEFS_HPP

#include <sway/ui/_stdafx.hpp>

namespace sway::ui {

class Builder;

class Painter;

using BuilderPtr_t = Builder *;
using BuilderSharedPtr_t = std::shared_ptr<Builder>;

using PainterSharedPtr_t = std::shared_ptr<Painter>;

}  // namespace sway::ui

#endif  // SWAY_UI_TYPEDEFS_HPP
