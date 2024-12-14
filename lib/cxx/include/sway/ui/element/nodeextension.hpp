#ifndef SWAY_UI_NODEEXTENSION_HPP
#define SWAY_UI_NODEEXTENSION_HPP

#include <sway/core.hpp>
#include <sway/ui/element/nodeutil.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

struct NodeExtension {
  template <typename TYPE>
  static auto getChild(core::container::Node *parent, const core::container::NodeIdx &idx) -> std::shared_ptr<TYPE> {
    return NodeUtil::cast<TYPE>(parent->getChildNode(idx));
  }

  template <typename TYPE>
  static auto getChild(core::container::Node *parent, const std::optional<core::container::NodeIdx> &idxOpt)
      -> std::shared_ptr<TYPE> {
    return idxOpt.has_value() ? NodeExtension::getChild<TYPE>(parent, idxOpt.value()) : nullptr;
  }
};

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_NODEEXTENSION_HPP
