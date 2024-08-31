#ifndef SWAY_UI_WIDGET_WIDGET_HPP
#define SWAY_UI_WIDGET_WIDGET_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ois.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/types.hpp>
#include <sway/ui/widget/appearance.hpp>
#include <sway/ui/widget/element.hpp>
#include <sway/ui/widget/types.hpp>
#include <sway/ui/widget/widgetevent.hpp>
#include <sway/ui/widget/widgeteventtypes.hpp>

#include <memory>
#include <optional>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

#define COL4F_RED math::col4f_t(0.85F, 0.33F, 0.17F, 1.0F)
#define COL4F_GREEN math::col4f_t(0.5F, 0.6F, 0.43F, 1.0F)
#define COL4F_BLUE math::col4f_t(0.4F, 0.53F, 0.56F, 1.0F)
#define COL4F_BEIGE math::col4f_t(0.81F, 0.75F, 0.68F, 1.0F)
#define COL4F_GRAY1 math::col4f_t(0.1F, 0.1F, 0.1F, 1.0F)
#define COL4F_GRAY2 math::col4f_t(0.18F, 0.17F, 0.16F, 1.0F)

#define COL4F_PURPLE 0x9900FFFF

NAMESPACE_BEGIN(widget)

class Widget : public Element {
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
#pragma region "Define aliases"

  using Ptr_t = WidgetPtr_t;
  using SharedPtr_t = WidgetSharedPtr_t;

#pragma endregion

#pragma region "Ctors/Dtor"

  Widget(BuilderPtr_t builder);

  virtual ~Widget() = default;

#pragma endregion

#pragma region "Base virtual methods"

  MTHD_VIRTUAL(void update());

  MTHD_VIRTUAL(void repaint(Painter::SharedPtr_t painter));

  MTHD_VIRTUAL(void onCursorPointerEnter());

  MTHD_VIRTUAL(void onCursorPointerLeave());

  MTHD_VIRTUAL(void onMouseClick());

#pragma endregion

  [[nodiscard]]
  auto hasRelated() -> bool;

  void updPosition();

#pragma region "Getters/Setters Size"

  void setSize(const math::size2f_t &size);

  void setSize(f32_t wdt, f32_t hgt);

  [[nodiscard]]
  auto getSize() const -> math::size2f_t;

#pragma endregion

  void setBackgroundColor(const math::col4f_t &col);

  [[nodiscard]]
  auto getBackgroundColor() const -> math::col4f_t;

  void setForegroundColor(const math::col4f_t &col);

  [[nodiscard]]
  auto getForegroundColor() const -> math::col4f_t;

  auto getChildAtPoint(const math::point2f_t &point) -> Widget *;

  // // wdt/hgt, margin, border, padding
  // auto getOuterSize() const -> math::size2f_t {
  //   const auto size = this->getSize();
  //   const auto outerWdt = size.getW() + margin_.getLR();
  //   const auto outerHgt = size.getH() + margin_.getTB();

  //   return math::size2f_t(outerWdt, outerHgt);
  // }

  void setEventFilter(core::evts::EventHandler::Ptr_t hdl);

  void setMouseFilter(ois::MouseFilter filter);

  [[nodiscard]]
  auto getMouseFilter() const -> ois::MouseFilter;

  void setAlignment(math::Alignment alignment);

protected:
  BuilderPtr_t builder_;
  ois::MouseFilter mouseFilter_;
  core::evts::EventHandler::Ptr_t eventFilter_;
  // math::rect4f_t innerRect_;  // wdt/hgt, padding
  // math::rect4f_t outerRect_;  // wdt/hgt, margin, border, padding
  math::Alignment alignment_;
  Appearance appearance_;

  bool containsPointer_;
  bool needsRepainting_;
};

NAMESPACE_END(widget)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_WIDGET_WIDGET_HPP
