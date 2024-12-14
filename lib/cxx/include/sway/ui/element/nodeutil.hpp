#ifndef SWAY_UI_NODEUTIL_HPP
#define SWAY_UI_NODEUTIL_HPP

#include <sway/core.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

struct NodeUtil {
  template <typename TYPE>
  static auto cast(core::container::Node::SharedPtr_t ptr) -> std::shared_ptr<TYPE> {
    return std::static_pointer_cast<TYPE>(ptr);
  }

  template <typename TYPE>
  static auto cast(std::optional<core::container::Node::SharedPtr_t> ptr) -> std::shared_ptr<TYPE> {
    return std::static_pointer_cast<TYPE>(ptr.value());
  }
};

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_NODEUTIL_HPP
