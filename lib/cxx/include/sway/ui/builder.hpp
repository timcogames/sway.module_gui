#ifndef SWAY_UI_BUILDER_HPP
#define SWAY_UI_BUILDER_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/ui/cursor.hpp>
#include <sway/ui/ft2/fontmanager.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/types.hpp>
#include <sway/ui/widget/widget.hpp>

#include <memory>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

class Builder : public core::foundation::Object {
  DECLARE_CLASS_METADATA(Builder, core::foundation::Object)
  DECLARE_CLASS_POINTER_ALIASES(Builder)

public:
  using ElementUnderPointer_t = widget::Widget::Ptr_t;

#pragma region "Ctors/Dtor"

  Builder(core::foundation::Context::Ptr_t context, Painter::SharedPtr_t painter);

  virtual ~Builder() = default;

#pragma endregion

  void initialize(ft2::Font::SharedPtr_t font, render::MaterialManagerSharedPtr_t materialMngr,
      std::shared_ptr<rms::ImageResourceManager> imgResMngr, std::shared_ptr<rms::GLSLResourceManager> glslResMngr);

  void deinit();

  void update();

  auto getRootWidget() -> widget::Widget::SharedPtr_t { return root_; }

  void setEventBus(core::evts::EventBus::SharedPtr_t evtbus) { evtbus_ = evtbus; }

  auto getEventBus() -> core::evts::EventBus::SharedPtr_t { return evtbus_; }

  void setCursorPoint(const math::point2f_t &pnt) { cursor_.pnt = pnt; }

  auto getCursor() const -> Cursor { return cursor_; }

  void updateWidgetUnderPointer(ElementUnderPointer_t target);

  auto getWidgetUnderPointer() -> ElementUnderPointer_t { return currWidgetUnderPointer_; }

  void handleMouseClick(u32_t state);

  auto getPainter() -> Painter::SharedPtr_t { return painter_; }

private:
  core::evts::EventBus::SharedPtr_t evtbus_;
  core::evts::EventBus::Subscriber_t subscriber_;
  ft2::FontManager::SharedPtr_t fontMngr_;
  Painter::SharedPtr_t painter_;
  widget::Widget::SharedPtr_t root_;

  struct ElementUnderPointerInfo {
    ElementUnderPointer_t element;
  };

  ElementUnderPointer_t currWidgetUnderPointer_;

  Cursor cursor_;
};

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_BUILDER_HPP
