#ifndef SWAY_UI_TYPES_HPP
#define SWAY_UI_TYPES_HPP

#include <sway/core.hpp>

#include <memory>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

class Builder;

using BuilderPtr_t = Builder *;
using BuilderSharedPtr_t = std::shared_ptr<Builder>;

NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_TYPES_HPP
