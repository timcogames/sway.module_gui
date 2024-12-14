#ifndef SWAY_UI_ELEMENT_NODECHAINEXTENSION_HPP
#define SWAY_UI_ELEMENT_NODECHAINEXTENSION_HPP

#include <sway/core.hpp>
#include <sway/ui/element/nodeindexextension.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

struct NodeChainExtension {
  /**
   * \~russian @brief Возвращает индекс предыдущего узла в цепочке.
   * @param[in] target Целевой индекс узла.
   * @return std::optional<core::container::NodeIdx>
   */
  static auto getPrevItem(const core::container::NodeIdx &target) -> std::optional<core::container::NodeIdx> {
    if (auto lastSegment = NodeIndexExtension::getLastSegment(target); lastSegment > GLOB_NULL) {
      auto prev = core::container::NodeIdx();
      prev.setChain(target.getParent(), lastSegment - 1);
      return prev;
    }

    return std::nullopt;
  }
};

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_ELEMENT_NODECHAINEXTENSION_HPP
