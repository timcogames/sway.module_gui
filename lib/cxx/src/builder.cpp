#include <sway/ui/builder.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

// lpcstr_t SymbolSet = "1234567890-=!@#$%^&*()_+\\|/><,.?~`';: "
//                      "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЪЫЭЮЯ"
//                      "абвгдеёжзийклмнопрстуфхцчшщьъыэюя"
//                      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//                      "abcdefghijklmnopqrstuvwxyz";

lpcstr_t SymbolSet = "1234567890-=!@#$%^&*()_+\\|/><,.?~`';: "
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                     "abcdefghijklmnopqrstuvwxyz";

Builder::Builder(core::foundation::Context *context, std::shared_ptr<Painter> painter)
    : core::foundation::Object(context)
    , painter_(painter) {
  root_ = std::make_shared<widget::Widget>();
}

void Builder::initialize(std::shared_ptr<ft2::Font> font, std::shared_ptr<render::MaterialManager> materialMngr,
    std::shared_ptr<rms::ImageResourceManager> imgResMngr, std::shared_ptr<rms::GLSLResourceManager> glslResMngr) {

  auto renderSubsystem = this->getContext()->getSubsystem<render::RenderSubsystem>("RenderSubsystem").value();

  painter_->initialize(font, renderSubsystem, materialMngr, imgResMngr, glslResMngr);

  // root_->setAbsolutePosition(0, 0);
  // root_->setSize(800, 600);

  root_->update();
  root_->draw(painter_);
}

NAMESPACE_END(ui)
NAMESPACE_END(sway)
