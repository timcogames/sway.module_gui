#ifndef SWAY_UI_LAYOUT_HPP
#define SWAY_UI_LAYOUT_HPP

#include <sway/core.hpp>
#include <sway/ui/layout/_typedefs.hpp>
#include <sway/ui/orientable.hpp>
#include <sway/ui/orientations.hpp>
#include <sway/ui/widget/widget.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class Layout : public LayoutItem, public Orientable {
public:
#pragma region "Static methods"

  /**
   * \~russian @brief Возвращает размер ячейки макета.
   * @param[in] elem Указатель на элемент макета.
   * @return math::size2f_t
   */
  static auto getCellSize(Element *elem) -> math::size2f_t;

#pragma endregion

#pragma region "Ctors/Dtor"

  Layout(BuilderTypedefs::Ptr_t builder, Orientation orien);

  DTOR_VIRTUAL_DEFAULT(Layout);

#pragma endregion
};

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_LAYOUT_HPP
