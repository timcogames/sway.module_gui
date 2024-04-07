#ifndef SWAY_UI_BUILDER_HPP
#define SWAY_UI_BUILDER_HPP

#include <sway/core.hpp>
#include <sway/ui/ft2/fontmanager.hpp>
#include <sway/ui/painter.hpp>
#include <sway/ui/widget/widget.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

struct Cursor {
  math::point2f_t pnt;
};

class Builder : public core::foundation::Object {
  DECLARE_CLASS_METADATA(Builder, core::foundation::Object)

public:
  Builder(core::foundation::Context *context, std::shared_ptr<Painter> painter);

  virtual ~Builder() = default;

  void initialize(std::shared_ptr<ft2::Font> font, std::shared_ptr<render::MaterialManager> materialMngr,
      std::shared_ptr<rms::ImageResourceManager> imgResMngr, std::shared_ptr<rms::GLSLResourceManager> glslResMngr);

  void deinit();

  void update();

  auto getRootWidget() -> std::shared_ptr<widget::Widget> { return root_; }

  void setWorldPointVec3F(math::vec3f_t pnt) { worldPoint_ = pnt; }

  void setEventBus(std::shared_ptr<core::evts::EventBus> evtbus) { evtbus_ = evtbus; }

  auto getEventBus() -> std::shared_ptr<core::evts::EventBus> { return evtbus_; }

  math::vec3f_t worldPoint_;

  void setCursorPoint(const math::point2f_t &pnt) { cursor_.pnt = pnt; }

  auto getCursor() const -> Cursor { return cursor_; }

  void updateWidgetUnderPointer(widget::Widget *target);

  void handleMouseClick();

private:
  std::shared_ptr<core::evts::EventBus> evtbus_;
  core::evts::EventBus::Subscriber subscriber_;
  std::shared_ptr<Painter> painter_;
  std::shared_ptr<ft2::FontManager> fontMngr_;
  std::shared_ptr<widget::Widget> root_;

  widget::Widget *currWidgetUnderPointer_;
  Cursor cursor_;
};

NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_BUILDER_HPP
