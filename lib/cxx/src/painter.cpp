#include <sway/ui/painter.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

Painter::Painter()
    : geom_(nullptr) {}

void Painter::initialize(std::shared_ptr<ft2::Font> font, const gapi::TextureCreateInfo &createInfo,
    std::shared_ptr<render::RenderSubsystem> subsystem, std::shared_ptr<render::MaterialManager> materialMngr,
    std::shared_ptr<rms::ImageResourceManager> imgResMngr, std::shared_ptr<rms::GLSLResourceManager> glslResMngr) {
  subqueue_ = subsystem->getQueueByIdx(0)->getSubqueues(render::RenderSubqueueGroup::OPAQUE)[0];

  mtrl_ = std::make_shared<render::Material>("material_ui", imgResMngr, glslResMngr);

  gapi::TextureCreateInfo texCreateInfo;
  texCreateInfo.target = gapi::TextureTarget::TEX_2D;
  texCreateInfo.size = font->getAtlasSize();
  texCreateInfo.format = gapi::PixelFormat::LUMINANCE_ALPHA;
  texCreateInfo.internalFormat = gapi::PixelFormat::LUMINANCE_ALPHA;
  texCreateInfo.dataType = core::ValueDataType::UBYTE;
  texCreateInfo.pixels = nullptr;
  texCreateInfo.mipLevels = 0;

  auto image = mtrl_->addImage(texCreateInfo, "diffuse_sampler");
  mtrl_->addEffect({"ui_vs", "ui_fs"});
  materialMngr->addMaterial(mtrl_);

  const auto wdt = font->getAtlasSize().getW() / font->maxSize_.getW();
  const auto hdt = font->getAtlasSize().getH() / font->maxSize_.getH();

  for (auto i = 0; i < font->glyphs_.size(); i++) {
    auto bi = font->getBitmapData(font->glyphs_[i]);

    auto symidx = font->glyphs_[i].idx;
    const auto x = symidx % wdt;
    const auto y = symidx / hdt;

    gapi::TextureSubdataDescriptor texSubdataDesc;
    texSubdataDesc.level = 0;
    texSubdataDesc.offset = math::point2i_t(x * font->maxSize_.getW(), y * font->maxSize_.getH());
    texSubdataDesc.size = bi.size;
    texSubdataDesc.format = gapi::PixelFormat::LUMINANCE_ALPHA;
    texSubdataDesc.type = core::ValueDataType::UBYTE;
    texSubdataDesc.pixels = bi.data;
    image->getTexture()->updateSubdata(texSubdataDesc);
  }

  std::array<gapi::VertexSemantic, 3> semantics = {
      gapi::VertexSemantic::POS, gapi::VertexSemantic::COL, gapi::VertexSemantic::TEXCOORD_0};

  auto geomShape_ = std::make_shared<render::PlaneArray<math::VertexTexCoordEx>>();
  geomShape_->useVertexSemanticSet(semantics);

  geom_ = std::make_shared<render::Geometry>(subsystem->getIdGenerator(), mtrl_->getEffect(), true);
  geom_->createArray(geomShape_);

  auto off = 0.0F;
  auto chr = "HELLO hello 12345";
  for (auto i = 0; i < strlen(chr); i++) {
    auto info = font->getCharInfo(chr[i]);
    if (info.has_value()) {
      auto symidx = info.value().symidx;
      const auto x = symidx % wdt;
      const auto y = symidx / hdt;

      auto offset_x = (f32_t)x * (f32_t)font->maxSize_.getW();
      auto offset_y = (f32_t)y * (f32_t)font->maxSize_.getH();

      math::rect4f_t uv;
      uv.setL(static_cast<f32_t>(offset_x) / static_cast<f32_t>(font->getAtlasSize().getW()));
      uv.setT(static_cast<f32_t>(offset_y) / static_cast<f32_t>(font->getAtlasSize().getH()));
      uv.setR(static_cast<f32_t>(offset_x + font->maxSize_.getW()) / static_cast<f32_t>(font->getAtlasSize().getW()));
      uv.setB(static_cast<f32_t>(offset_y + font->maxSize_.getH()) / static_cast<f32_t>(font->getAtlasSize().getH()));

      geomShape_->updateVertices(math::point2f_t(off, 0.0F), math::size2f_t(0.1F, 0.1F), uv);
      off += 0.05F;
    }
  }

  gapi::BufferSubdataDescriptor subdataDesc;
  subdataDesc.offset = 0;
  subdataDesc.size = geomShape_->data_->getVtxCount();
  subdataDesc.data = geomShape_->data_->getVtxRawdata();
  auto bufset = geom_->getBufferSet();
  bufset.vbo->updateSubdata(subdataDesc);
}

void Painter::onUpdate(math::mat4f_t tfrm, math::mat4f_t proj, math::mat4f_t view, f32_t dtime) {
  render::pipeline::ForwardRenderCommand cmd;
  cmd.stage = 0;
  cmd.blendDesc.enabled = true;
  cmd.blendDesc.src = gapi::BlendFn::SRC_ALPHA;
  cmd.blendDesc.dst = gapi::BlendFn::ONE_MINUS_SRC_ALPHA;
  cmd.blendDesc.mask = true;
  cmd.rasterizerDesc.mode = gapi::CullFace::BACK;
  cmd.rasterizerDesc.ccw = false;
  cmd.depthDesc.enabled = true;
  cmd.depthDesc.func = gapi::CompareFn::LESS;
  cmd.depthDesc.mask = true;
  cmd.depthDesc.near = 0;
  cmd.depthDesc.far = 0;
  cmd.stencilDesc.enabled = true;
  cmd.stencilDesc.front.func = gapi::CompareFn::ALWAYS;
  cmd.stencilDesc.front.fail = gapi::StencilOp::KEEP;
  cmd.stencilDesc.front.depthFail = gapi::StencilOp::KEEP;
  cmd.stencilDesc.front.depthPass = gapi::StencilOp::REPLACE;
  cmd.stencilDesc.front.rmask = 0xFFFFFF;
  cmd.stencilDesc.front.wmask = cmd.stencilDesc.front.rmask;
  cmd.stencilDesc.front.reference = 1;
  cmd.stencilDesc.back = cmd.stencilDesc.front;
  cmd.geometry = geom_;
  cmd.material = mtrl_;
  cmd.tfrm = tfrm;
  cmd.proj = proj;
  cmd.view = view;

  subqueue_->post(cmd);
}

NAMESPACE_END(ui)
NAMESPACE_END(sway)
