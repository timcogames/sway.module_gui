#ifndef SWAY_UI_LAYOUT_LAYOUTITEM_HPP
#define SWAY_UI_LAYOUT_LAYOUTITEM_HPP

#include <sway/core.hpp>
#include <sway/ois.hpp>
#include <sway/ui/element/_typedefs.hpp>
#include <sway/ui/element/element.hpp>
#include <sway/ui/layout/_typedefs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class LayoutItem : public Element {
public:
#pragma region "Ctors/Dtor"

  LayoutItem();

  DTOR_VIRTUAL_DEFAULT(LayoutItem);

#pragma endregion

#pragma region "Base virtual methods"

  MTHD_VIRTUAL(void update()) {}

#pragma endregion

  void setMouseFilter(ois::MouseFilter::Enum filter) { mouseFilter_ = filter; }

  [[nodiscard]] auto getMouseFilter() const -> ois::MouseFilter::Enum { return mouseFilter_; }

private:
  ois::MouseFilter::Enum mouseFilter_;
};

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_LAYOUT_LAYOUTITEM_HPP
