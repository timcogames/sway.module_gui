#ifndef SWAY_UI_LAYOUTITEM_HPP
#define SWAY_UI_LAYOUTITEM_HPP

#include <sway/core.hpp>
#include <sway/ois.hpp>
#include <sway/render/updatable.hpp>
#include <sway/ui/element/_typedefs.hpp>
#include <sway/ui/element/element.hpp>
#include <sway/ui/layout/_typedefs.hpp>

namespace sway::ui {

class LayoutItem : public Element, public render::Updatable {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  LayoutItem();

  virtual ~LayoutItem() = default;

  /** @} */
#pragma endregion

#pragma region "Overridden Updatable methods"

  virtual void update() {}

#pragma endregion

#pragma region "Overridden Element methods"

  void recursiveUpdateItemOffset(const math::point2f_t offset) override;

#pragma endregion

  void setMouseFilter(ois::MouseFilter filter) { mouseFilter_ = filter; }

  [[nodiscard]] auto getMouseFilter() const -> ois::MouseFilter { return mouseFilter_; }

private:
  ois::MouseFilter mouseFilter_;
};

}  // namespace sway::ui

#endif  // SWAY_UI_LAYOUTITEM_HPP
