#include <sway/render/procedurals/prims/quadrilateral.hpp>
#include <sway/ui/painter.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

Painter::Painter()
    : textGeom_(nullptr)
    , geomBatchChunkSize_(0) {}

void Painter::initialize(std::shared_ptr<ft2::Font> font, std::shared_ptr<render::RenderSubsystem> subsystem,
    std::shared_ptr<render::MaterialManager> materialMngr, std::shared_ptr<rms::ImageResourceManager> imgResMngr,
    std::shared_ptr<rms::GLSLResourceManager> glslResMngr) {

  font_ = font;

  subqueue_ = std::make_shared<render::RenderSubqueue>();
  subqueue_->initialize();

  queue_ = subsystem->createQueue(core::detail::toUnderlying(core::intrusive::Priority::VERY_HIGH));
  queue_->addSubqueue(subqueue_);

  subqueue_ = subsystem->getQueueByPriority(core::detail::toUnderlying(core::intrusive::Priority::VERY_HIGH))
                  ->getSubqueues(render::RenderSubqueueGroup::OPAQUE)[0];

  rectMtrl_ = std::make_shared<render::Material>("material_ui_rect", imgResMngr, glslResMngr);
  rectMtrl_->addEffect({"ui_rect_vs", "ui_rect_fs"});
  materialMngr->addMaterial(rectMtrl_);

  textMtrl_ = std::make_shared<render::Material>("material_ui_text", imgResMngr, glslResMngr);
  textMtrl_->addEffect({"ui_text_vs", "ui_text_fs"});
  materialMngr->addMaterial(textMtrl_);

  gapi::TextureCreateInfo texCreateInfo;
  texCreateInfo.target = gapi::TextureTarget::TEX_2D;
  texCreateInfo.size = font->getAtlasSize();
  texCreateInfo.format = gapi::PixelFormat::LUMINANCE_ALPHA;
  texCreateInfo.internalFormat = gapi::PixelFormat::LUMINANCE_ALPHA;
  texCreateInfo.dataType = core::ValueDataType::UBYTE;
  texCreateInfo.pixels = nullptr;
  texCreateInfo.mipLevels = 0;
  auto image = textMtrl_->addImage(texCreateInfo, "diffuse_sampler");

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

  // --------------

  auto numInstances = 2;
  rectGeomShape_ = std::make_shared<render::procedurals::prims::Quadrilateral<math::VertexColor>>(numInstances);
  rectGeomShape_->useVertexSemanticSet({gapi::VertexSemantic::POS, gapi::VertexSemantic::COL});

  geomBuilder_ = render::GeomBuilder::create(subsystem->getIdGenerator());
  geomBuilder_->reserve(1);
  geomBuilder_->createInstance(0);

  render::GeometryCreateInfo geomCreateInfo;
  geomCreateInfo.indexed = true;
  geomCreateInfo.topology = gapi::TopologyType::TRIANGLE_LIST;
  geomCreateInfo.bo[render::Constants::IDX_VBO].desc.usage = gapi::BufferUsage::DYNAMIC;
  geomCreateInfo.bo[render::Constants::IDX_VBO].desc.byteStride = sizeof(math::VertexColor);
  geomCreateInfo.bo[render::Constants::IDX_VBO].desc.capacity = rectGeomShape_->data_->getVtxSize();
  geomCreateInfo.bo[render::Constants::IDX_VBO].data = nullptr;

  geomCreateInfo.bo[render::Constants::IDX_EBO].desc.usage = gapi::BufferUsage::STATIC;
  geomCreateInfo.bo[render::Constants::IDX_EBO].desc.byteStride = sizeof(u32_t);
  geomCreateInfo.bo[render::Constants::IDX_EBO].desc.capacity = rectGeomShape_->data_->getElmSize();
  geomCreateInfo.bo[render::Constants::IDX_EBO].data = rectGeomShape_->data_->getElements();
  rectGeom_ = static_cast<render::GeomInstance *>(geomBuilder_->getGeometry(0));
  rectGeom_->create(geomCreateInfo, rectMtrl_->getEffect(), rectGeomShape_->getVertexAttribs());

  // --------------

  std::array<gapi::VertexSemantic, 3> textSemantics = {
      gapi::VertexSemantic::POS, gapi::VertexSemantic::COL, gapi::VertexSemantic::TEXCOORD_0};
  textGeomShape_ = std::make_shared<render::PlaneArray<math::VertexTexCoord>>();
  textGeomShape_->useVertexSemanticSet(textSemantics);
  textGeom_ = std::make_shared<render::Geometry>(subsystem->getIdGenerator(), textMtrl_->getEffect(), true);
  textGeom_->createArray(textGeomShape_);
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

  auto rectOffset = 0;
  auto rectOffsetIdx = 0;
  auto textOffset = 0;
  auto test = false;

  for (auto chunkIndex = 0; chunkIndex < geomBatchChunkSize_; ++chunkIndex) {
    const GeometryBatchChunk &chunk = geomBatchChunks_[chunkIndex];

    if (chunk.type == GeometryBatchChunkType::RECT) {
      auto rect = math::rect4f_t(chunk.rect.x, chunk.rect.y, chunk.rect.w, chunk.rect.h);
      auto rectColor = math::col4f_t(chunk.rect.r, chunk.rect.g, chunk.rect.b, chunk.rect.a);
      rectGeomShape_->update(rectOffsetIdx, rect, rectColor);

      // gapi::BufferSubdataDescriptor subdataDesc;
      // subdataDesc.offset = rectOffset;
      // subdataDesc.size = 4 * sizeof(math::VertexColor);
      // subdataDesc.data = rectGeomShape_->data_->getVertices(0, 8);

      if (rectGeom_->getBuffer(render::Constants::IDX_VBO).has_value()) {
        // rectGeom_->getVertexArray()->bind();
        // rectGeom_->getBuffer(render::Constants::IDX_VBO).value()->updateSubdata(subdataDesc);
        // rectGeom_->getVertexArray()->unbind();

        auto *data = rectGeom_->getBuffer(render::Constants::IDX_VBO).value()->map();
        memcpy(data, rectGeomShape_->data_->getVertices(0, 8), 8 * sizeof(math::VertexColor));
        rectGeom_->getBuffer(render::Constants::IDX_VBO).value()->unmap();
      }

      rectOffset += 4 * sizeof(math::VertexColor);
      rectOffsetIdx += 4;
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

          textGeomShape_->updateVertices(
              math::point2f_t(pos.getX() + vert_offset_x,
                  pos.getY() + ((f32_t)bearing.getY() / static_cast<f32_t>(font_->getAtlasSize().getH())) - symSizeH),
              math::size2f_t(symSizeW, symSizeH),
              // math::col4f_t(chunk.text.r, chunk.text.g, chunk.text.b, chunk.text.a),
              uv);

          vert_offset_x += ((f32_t)bearing.getX() / static_cast<f32_t>(font_->getAtlasSize().getW())) + symSizeW;
        }
      }

      gapi::BufferSubdataDescriptor subdataDesc;
      subdataDesc.offset = textOffset;
      subdataDesc.size = textGeomShape_->data_->getVtxCount();
      subdataDesc.data = textGeomShape_->data_->getVtxRawdata();
      auto bufset = textGeom_->getBufferSet();
      bufset.vbo->updateSubdata(subdataDesc);

      textOffset += (4 * sizeof(math::VertexTexCoord)) * strlen(chunk.text.text);
    }
  }
}

void Painter::onUpdate(math::mat4f_t tfrm, math::mat4f_t proj, math::mat4f_t view, f32_t dtime) {
  this->onUpdateBatchChunks();

  geomBatchChunkSize_ = 0;

  render::pipeline::ForwardRenderCommand cmd;
  cmd.stage = 0;
  cmd.blendDesc.enabled = false;
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
  // cmd.geometry = rectGeom_;
  cmd.geom = rectGeom_;
  cmd.material = rectMtrl_;
  cmd.tfrm = tfrm;
  cmd.proj = proj;
  cmd.view = math::mat4f_t();

  subqueue_->post(cmd);

  render::pipeline::ForwardRenderCommand cmd2;
  cmd2.stage = 0;
  cmd2.blendDesc.enabled = true;
  cmd2.blendDesc.src = gapi::BlendFn::SRC_ALPHA;
  cmd2.blendDesc.dst = gapi::BlendFn::ONE_MINUS_SRC_ALPHA;
  cmd2.blendDesc.mask = true;
  cmd2.rasterizerDesc.mode = gapi::CullFace::BACK;
  cmd2.rasterizerDesc.ccw = false;
  cmd2.depthDesc.enabled = true;
  cmd2.depthDesc.func = gapi::CompareFn::LESS;
  cmd2.depthDesc.mask = true;
  cmd2.depthDesc.near = 0;
  cmd2.depthDesc.far = 0;
  cmd2.stencilDesc.enabled = true;
  cmd2.stencilDesc.front.func = gapi::CompareFn::ALWAYS;
  cmd2.stencilDesc.front.fail = gapi::StencilOp::KEEP;
  cmd2.stencilDesc.front.depthFail = gapi::StencilOp::KEEP;
  cmd2.stencilDesc.front.depthPass = gapi::StencilOp::REPLACE;
  cmd2.stencilDesc.front.rmask = 0xFFFFFF;
  cmd2.stencilDesc.front.wmask = cmd2.stencilDesc.front.rmask;
  cmd2.stencilDesc.front.reference = 1;
  cmd2.stencilDesc.back = cmd2.stencilDesc.front;
  cmd2.geometry = textGeom_;
  cmd2.material = textMtrl_;
  cmd2.tfrm = tfrm;
  cmd2.proj = proj;
  cmd2.view = view;

  subqueue_->post(cmd2);
}

NAMESPACE_END(ui)
NAMESPACE_END(sway)
