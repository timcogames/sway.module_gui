#ifndef SWAY_UI_TYPEDEFS_HPP
#define SWAY_UI_TYPEDEFS_HPP

#include <sway/core.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class Builder;
namespace BuilderTypedefs {
using Ptr_t = Builder *;
using SharedPtr_t = std::shared_ptr<Builder>;
}  // namespace BuilderTypedefs

class Painter;
namespace PainterTypedefs {
using SharedPtr_t = std::shared_ptr<Painter>;
}  // namespace PainterTypedefs

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_TYPEDEFS_HPP
