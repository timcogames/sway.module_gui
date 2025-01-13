#ifndef SWAY_UI_BUILDER_HPP
#define SWAY_UI_BUILDER_HPP

#include <sway/ui/_stdafx.hpp>
#include <sway/ui/_typedefs.hpp>
#include <sway/ui/cursor.hpp>
#include <sway/ui/element/elementunderpointerinfo.hpp>
#include <sway/ui/ft2/fontmanager.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/_typedefs.hpp>
#include <sway/ui/widget/widget.hpp>

namespace sway::ui {

class Builder : public core::Object {
  DECLARE_CLASS_METADATA(Builder, core::Object)

public:
#pragma region "Pointer aliases"
  /** \~english @name Pointer aliases */ /** \~russian @name Типы указателей */

  using Ptr_t = BuilderPtr_t;
  using SharedPtr_t = BuilderSharedPtr_t;

  /** @{ */
#pragma endregion

#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  Builder(core::typedefs::ContextPtr_t context);

  virtual ~Builder() = default;

  /** @} */
#pragma endregion

  void initialize();

  void deinit();

  void update();

  auto getRootWidget() -> WidgetSharedPtr_t { return root_; }

  void setEventBus(core::EventBusTypedefs::SharedPtr_t evtbus) { evtbus_ = evtbus; }

  auto getEventBus() -> core::EventBusTypedefs::SharedPtr_t { return evtbus_; }

  void setCursorPoint(const math::point2f_t &pnt) { cursor_.pnt = pnt; }

  auto getCursor() const -> Cursor { return cursor_; }

  void updateWidgetUnderPointer(ElementUnderPointer_t target);

  auto getWidgetUnderPointer() -> ElementUnderPointer_t { return currWidgetUnderPointer_; }

  void handleMouseClick(u32_t state);

  void setPainter(PainterSharedPtr_t painter) { painter_ = painter; }

  auto getPainter() -> PainterSharedPtr_t { return painter_; }

private:
  core::EventBusTypedefs::SharedPtr_t evtbus_;
  core::Subscribable::Subscriber_t subscriber_;
  ft2::FontManager::SharedPtr_t fontMngr_;
  PainterSharedPtr_t painter_;
  WidgetSharedPtr_t root_;

  ElementUnderPointer_t currWidgetUnderPointer_;

  Cursor cursor_;
};

}  // namespace sway::ui

#endif  // SWAY_UI_BUILDER_HPP
