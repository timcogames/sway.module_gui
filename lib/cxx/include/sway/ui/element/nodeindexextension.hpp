#ifndef SWAY_UI_ELEMENT_NODEINDEXEXTENSION_HPP
#define SWAY_UI_ELEMENT_NODEINDEXEXTENSION_HPP

#include <sway/core.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

struct NodeIndexExtension {
  /**
   * \~russian @brief Возвращает последний сегмент в индексе целевого узла.
   * @param[in] target Целевой индекс узла.
   * @return core::container::NodeIdx::ChainItemIndex_t
   */
  static auto getLastSegment(const core::container::NodeIdx &target) -> core::container::NodeIdx::ChainItemIndex_t {
    return target.getIdxAt(target.getDepth() - 1);
  }
};

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_ELEMENT_NODEINDEXEXTENSION_HPP
