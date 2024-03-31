#include <sway/ois/web/emsmouse.hpp>
#include <sway/ui/builder.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

struct WidgetEventHandler : public core::evts::EventHandler {
  WidgetEventHandler(Builder *builder)
      : core::evts::EventHandler()
      , builder_(builder) {}

  ~WidgetEventHandler() override = default;

  // clang-format off
  MTHD_OVERRIDE(auto invoke(const std::unique_ptr<core::foundation::Event> &event) -> bool) final {  // clang-format on
    if (ois::InputEventUtil::isMouseEvent(event)) {
      onMouseEvent(ois::InputEventUtil::asMouseEvent(event));
    }

    return true;
  }

  void onMouseEvent(ois::MouseEvent *event) {
    auto *context = static_cast<Framework *>(state_->getContext());
    auto mouseEventData = event->getConcreteData<ois::MouseEventData>();

    if (mouseEventData.state == core::detail::toUnderlying(ois::InputActionState::PRESSED)) {
      if (mouseEventData.btnCode == core::detail::toUnderlying(ois::MouseButtonCode::LMB)) {
        // Empty
      }
    }

    if (event->type() == core::detail::toUnderlying(ois::InputActionType::MOUSE_MOVED)) {
      if (builder_->getRootWidget()->getChildAt(
              math::point2f_t(builder_->worldPoint_.getX(), builder_->worldPoint_.getY()))) {
        // Empty
      }
    }
  }

private:
  Builder *builder_;
};

Builder::Builder(core::foundation::Context *context, std::shared_ptr<Painter> painter)
    : core::foundation::Object(context)
    , painter_(painter) {
  root_ = std::make_shared<widget::Widget>(this);
}

void Builder::initialize(std::shared_ptr<ft2::Font> font, std::shared_ptr<render::MaterialManager> materialMngr,
    std::shared_ptr<rms::ImageResourceManager> imgResMngr, std::shared_ptr<rms::GLSLResourceManager> glslResMngr) {
  auto ctx = this->getContext();

  auto renderSubsystem = ctx->getSubsystem<render::RenderSubsystem>("RenderSubsystem").value();

  painter_->initialize(font, renderSubsystem, materialMngr, imgResMngr, glslResMngr);

  subscriber_ = evtbus_->subscribe(new WidgetEventHandler(this));
  // evtbus_->unsubscribe(subscriber_);

  // root_->setAbsolutePosition(0, 0);
  // root_->setSize(800, 600);
}

void Builder::update() {
  root_->update();
  root_->paintEvent(painter_);
}

NAMESPACE_END(ui)
NAMESPACE_END(sway)
