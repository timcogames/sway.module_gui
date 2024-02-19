#include <sway/ui/painter.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

Painter::Painter()
    : geom_(nullptr)
    , geomBatchChunkSize_(0) {}

void Painter::initialize(std::shared_ptr<ft2::Font> font, std::shared_ptr<render::RenderSubsystem> subsystem,
    std::shared_ptr<render::MaterialManager> materialMngr, std::shared_ptr<rms::ImageResourceManager> imgResMngr,
    std::shared_ptr<rms::GLSLResourceManager> glslResMngr) {

  font_ = font;

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

  const auto wdt = font_->getAtlasSize().getW() / font_->maxSize_.getW();
  const auto hdt = font_->getAtlasSize().getH() / font_->maxSize_.getH();

  for (auto i = 0; i < font_->glyphs_.size(); i++) {
    auto bi = font_->getBitmapData(font_->glyphs_[i]);

    auto symidx = font_->glyphs_[i].idx;
    const auto x = symidx % wdt;
    const auto y = symidx / hdt;

    gapi::TextureSubdataDescriptor texSubdataDesc;
    texSubdataDesc.level = 0;
    texSubdataDesc.offset = math::point2i_t(x * font_->maxSize_.getW(), y * font_->maxSize_.getH());
    texSubdataDesc.size = bi.size;
    texSubdataDesc.format = gapi::PixelFormat::LUMINANCE_ALPHA;
    texSubdataDesc.type = core::ValueDataType::UBYTE;
    texSubdataDesc.pixels = bi.data;
    image->getTexture()->updateSubdata(texSubdataDesc);
  }

  std::array<gapi::VertexSemantic, 3> semantics = {
      gapi::VertexSemantic::POS, gapi::VertexSemantic::COL, gapi::VertexSemantic::TEXCOORD_0};

  geomShape_ = std::make_shared<render::PlaneArray<math::VertexTexCoordEx>>();
  geomShape_->useVertexSemanticSet(semantics);

  geom_ = std::make_shared<render::Geometry>(subsystem->getIdGenerator(), mtrl_->getEffect(), true);
  geom_->createArray(geomShape_);
}

void Painter::drawRect(f32_t x, f32_t y, f32_t w, f32_t h, math::col4f_t col) {
  if (geomBatchChunkSize_ >= GEOMERTY_BATCH_CHUNK_SIZE) {
    return;
  }

  GeometryBatchChunk &chunk = geomBatchChunks_[geomBatchChunkSize_++];
  chunk.type = GeometryBatchChunkType::RECT;
  chunk.rect.x = x;
  chunk.rect.y = y;
  chunk.rect.w = w;
  chunk.rect.h = h;
  chunk.rect.r = col.getR();
  chunk.rect.g = col.getG();
  chunk.rect.b = col.getB();
  chunk.rect.a = col.getA();
}

void Painter::drawText(f32_t x, f32_t y, f32_t w, f32_t h, math::col4f_t col, lpcstr_t text) {
  if (geomBatchChunkSize_ >= GEOMERTY_BATCH_CHUNK_SIZE) {
    return;
  }

  GeometryBatchChunk &chunk = geomBatchChunks_[geomBatchChunkSize_++];
  chunk.type = GeometryBatchChunkType::TEXT;
  chunk.text.x = x;
  chunk.text.y = y;
  chunk.text.w = w;
  chunk.text.h = h;
  chunk.text.r = col.getR();
  chunk.text.g = col.getG();
  chunk.text.b = col.getB();
  chunk.text.a = col.getA();
  chunk.text.text = text;
}

void Painter::onUpdateBatchChunks() {
  const auto wdt = font_->getAtlasSize().getW() / font_->maxSize_.getW();
  const auto hdt = font_->getAtlasSize().getH() / font_->maxSize_.getH();

  auto offset = 0;

  for (auto chunkIndex = 0; chunkIndex < geomBatchChunkSize_; ++chunkIndex) {
    const GeometryBatchChunk &chunk = geomBatchChunks_[chunkIndex];

    if (chunk.type == GeometryBatchChunkType::RECT) {
      auto pos = math::point2f_t(chunk.rect.x, chunk.rect.y);
      auto size = math::size2f_t(chunk.rect.w, chunk.rect.h);

      math::rect4f_t uv;
      uv.setL(0.0F);
      uv.setT(0.0F);
      uv.setR(1.0F);
      uv.setB(1.0F);

      geomShape_->updateVertices(pos, size, uv);

      gapi::BufferSubdataDescriptor subdataDesc;
      subdataDesc.offset = offset;
      subdataDesc.size = geomShape_->data_->getVtxCount();
      subdataDesc.data = geomShape_->data_->getVtxRawdata();
      auto bufset = geom_->getBufferSet();
      bufset.vbo->updateSubdata(subdataDesc);

      offset += 4 * sizeof(math::VertexTexCoordEx);

    } else if (chunk.type == GeometryBatchChunkType::TEXT) {
      auto pos = math::point2f_t(chunk.text.x, chunk.text.y);
      auto size = math::size2f_t(chunk.text.w, chunk.text.h);

      auto vert_offset_x = 0.0F;

      for (auto i = 0; i < strlen(chunk.text.text); i++) {
        auto info = font_->getCharInfo(chunk.text.text[i]);
        if (info.has_value()) {
          auto symidx = info.value().symidx;
          const auto x = symidx % wdt;
          const auto y = symidx / hdt;

          auto bearing = info.value().bearing;
          auto advance = info.value().advance;

          auto symSizeW = static_cast<f32_t>(font_->maxSize_.getW()) / static_cast<f32_t>(font_->getAtlasSize().getW());
          auto symSizeH = static_cast<f32_t>(font_->maxSize_.getH()) / static_cast<f32_t>(font_->getAtlasSize().getH());

          auto offset_x = (f32_t)x * (f32_t)font_->maxSize_.getW();
          auto offset_y = (f32_t)y * (f32_t)font_->maxSize_.getH();

          math::rect4f_t uv;
          uv.setL(static_cast<f32_t>(offset_x) / static_cast<f32_t>(font_->getAtlasSize().getW()));
          uv.setT(static_cast<f32_t>(offset_y) / static_cast<f32_t>(font_->getAtlasSize().getH()));
          uv.setR(
              static_cast<f32_t>(offset_x + font_->maxSize_.getW()) / static_cast<f32_t>(font_->getAtlasSize().getW()));
          uv.setB(
              static_cast<f32_t>(offset_y + font_->maxSize_.getH()) / static_cast<f32_t>(font_->getAtlasSize().getH()));

          geomShape_->updateVertices(
              math::point2f_t(pos.getX() + vert_offset_x,
                  pos.getY() + ((f32_t)bearing.getY() / static_cast<f32_t>(font_->getAtlasSize().getH())) - symSizeH),
              math::size2f_t(symSizeW, symSizeH), uv);

          vert_offset_x += ((f32_t)bearing.getX() / static_cast<f32_t>(font_->getAtlasSize().getW())) + symSizeW;
        }
      }

      gapi::BufferSubdataDescriptor subdataDesc;
      subdataDesc.offset = offset;
      subdataDesc.size = geomShape_->data_->getVtxCount();
      subdataDesc.data = geomShape_->data_->getVtxRawdata();
      auto bufset = geom_->getBufferSet();
      bufset.vbo->updateSubdata(subdataDesc);

      offset += (4 * sizeof(math::VertexTexCoordEx)) * strlen(chunk.text.text);
    }
  }

  // if (geomBatchChunkSize_ == 0) {
  //   gapi::BufferSubdataDescriptor subdataDesc;
  //   subdataDesc.offset = 0;
  //   subdataDesc.size = geomShape_->data_->getVtxCount();
  //   subdataDesc.data = nullptr;
  //   auto bufset = geom_->getBufferSet();
  //   bufset.vbo->updateSubdata(subdataDesc);
  // }
}

void Painter::onUpdate(math::mat4f_t tfrm, math::mat4f_t proj, math::mat4f_t view, f32_t dtime) {
  geomShape_->clear();
  this->onUpdateBatchChunks();

  // if (geomBatchChunkSize_ == 0) {
  //   return;
  // }

  geomBatchChunkSize_ = 0;

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
