#ifndef SWAY_UI_WIDGET_WIDGET_HPP
#define SWAY_UI_WIDGET_WIDGET_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ois.hpp>
#include <sway/ui/_typedefs.hpp>
#include <sway/ui/element/_typedefs.hpp>
#include <sway/ui/element/element.hpp>
#include <sway/ui/layout/layoutitem.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/appearance.hpp>
#include <sway/ui/widget/typedefs.hpp>
#include <sway/ui/widget/widgetevent.hpp>
#include <sway/ui/widget/widgeteventtypes.hpp>

#include <memory>
#include <optional>

namespace sway::ui {

#define COL4F_RED math::col4f_t(0.85F, 0.33F, 0.17F, 1.0F)
#define COL4F_GREEN math::col4f_t(0.5F, 0.6F, 0.43F, 1.0F)
#define COL4F_BLUE math::col4f_t(0.4F, 0.53F, 0.56F, 1.0F)
#define COL4F_BEIGE math::col4f_t(0.81F, 0.75F, 0.68F, 1.0F)
#define COL4F_GRAY1 math::col4f_t(0.1F, 0.1F, 0.1F, 1.0F)
#define COL4F_GRAY2 math::col4f_t(0.18F, 0.17F, 0.16F, 1.0F)

#define COL4F_PURPLE 0x9900FFFF

// struct Groupable {
//   Guid ID;
//   Guid ParentID;
//   bool IsGroup;
// };

// struct Selectable {
//   bool IsSelected;
// };

// Category = Behavior
// struct Focusable {};

class Widget : public LayoutItem {
  DECLARE_EVENT(EVT_POINTER_ENTER, PointerEnter)
  DECLARE_EVENT(EVT_POINTER_LEAVE, PointerLeave)
  DECLARE_EVENT(EVT_MOUSE_CLICKED, MouseClicked)

  // DECLARE_EVENT(EVT_PRESSED, Pressed)
  // DECLARE_EVENT(EVT_RELEASED, Released)
  // DECLARE_EVENT(EVT_CLICKED, Clicked)
  // DECLARE_EVENT(EVT_ENTER, Enter)
  // DECLARE_EVENT(EVT_LEAVE, Leave)
  // DECLARE_EVENT(EVT_ACTIVATE, Activate)
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  Widget(BuilderTypedefs::Ptr_t builder);

  virtual ~Widget() = default;

  /** @} */
#pragma endregion

#pragma region "Base virtual methods"

  MTHD_VIRTUAL(void repaint(PainterTypedefs::SharedPtr_t painter));

  MTHD_VIRTUAL(void onCursorPointerEnter());

  MTHD_VIRTUAL(void onCursorPointerLeave());

  MTHD_VIRTUAL(void onMouseClick(u32_t state));

#pragma endregion

#pragma region "Overridden LayoutItem methods"

  MTHD_VIRTUAL(void update());

#pragma endregion

  void setBackgroundColor(const math::col4f_t &col);

  [[nodiscard]] auto getBackgroundColor() const -> math::col4f_t;

  void setForegroundColor(const math::col4f_t &col);

  [[nodiscard]] auto getForegroundColor() const -> math::col4f_t;

  auto getChildAtPoint(const math::point2f_t &point) -> Widget *;

  // void setEventFilter(core::evts::EventHandlerTypedefs::Ptr_t hdl);

  void setAlignment(math::Alignment alignment);

protected:
  BuilderTypedefs::Ptr_t builder_;
  // core::evts::EventHandlerTypedefs::Ptr_t eventFilter_;
  // math::rect4f_t innerRect_;  // wdt/hgt, padding
  // math::rect4f_t outerRect_;  // wdt/hgt, margin, border, padding
  Appearance appearance_;

  bool containsPointer_;
  bool needsRepainting_;
  bool needToUpdate_;
};

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGET_WIDGET_HPP
