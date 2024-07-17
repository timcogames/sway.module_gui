#ifndef SWAY_UI_BUILDER_HPP
#define SWAY_UI_BUILDER_HPP

#include <sway/core.hpp>
#include <sway/ui/cursor.hpp>
#include <sway/ui/ft2/fontmanager.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/widget.hpp>

#include <memory>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

class Builder : public core::foundation::Object {
  DECLARE_CLASS_METADATA(Builder, core::foundation::Object)

public:
  using Ptr_t = Builder *;
  using SharedPtr_t = std::shared_ptr<Builder>;

  Builder(core::foundation::Context *context, Painter::SharedPtr_t painter);

  virtual ~Builder() = default;

  void initialize(std::shared_ptr<ft2::Font> font, std::shared_ptr<render::MaterialManager> materialMngr,
      std::shared_ptr<rms::ImageResourceManager> imgResMngr, std::shared_ptr<rms::GLSLResourceManager> glslResMngr);

  void deinit();

  void update();

  auto getRootWidget() -> widget::Widget::SharedPtr_t { return root_; }

  void setEventBus(std::shared_ptr<core::evts::EventBus> evtbus) { evtbus_ = evtbus; }

  auto getEventBus() -> std::shared_ptr<core::evts::EventBus> { return evtbus_; }

  void setCursorPoint(const math::point2f_t &pnt) { cursor_.pnt = pnt; }

  auto getCursor() const -> Cursor { return cursor_; }

  void updateWidgetUnderPointer(widget::Widget::Ptr_t target);

  auto getWidgetUnderPointer() -> widget::Widget::Ptr_t { return currWidgetUnderPointer_; }

  void handleMouseClick();

private:
  std::shared_ptr<core::evts::EventBus> evtbus_;
  core::evts::EventBus::Subscriber subscriber_;
  Painter::SharedPtr_t painter_;
  std::shared_ptr<ft2::FontManager> fontMngr_;
  widget::Widget::SharedPtr_t root_;
  widget::Widget::Ptr_t currWidgetUnderPointer_;
  Cursor cursor_;
};

NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_BUILDER_HPP
