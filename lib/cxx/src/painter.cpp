#include <sway/render/procedurals/prims/quadrilateral.hpp>
#include <sway/ui/painter.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

static int maxCharTall = 0;
static math::point2i_t pos;

Painter::Painter()
    : geomBatchChunkSize_(0) {}

Painter::~Painter() {}

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

  // const auto wdt = font_->getAtlasSize().getW() / font_->maxSize_.getW();
  // const auto hdt = font_->getAtlasSize().getH() / font_->maxSize_.getH();

  for (auto i = 0; i < font_->glyphs_.size(); i++) {
    auto bi = font_->getBitmapData(font_->glyphs_[i]);

    auto symidx = font_->glyphs_[i].idx;
    // const auto x = i % wdt;
    // const auto y = i / hdt;

    if (font_->maxSize_.getW() + pos.getX() > font_->getAtlasSize().getW()) {
      int newLineY = pos.getY() + maxCharTall;

      pos.set(0, newLineY);
      maxCharTall = 0;
    }

    gapi::TextureSubdataDescriptor texSubdataDesc;
    texSubdataDesc.level = 0;
    texSubdataDesc.offset = pos;
    texSubdataDesc.size = bi.size;
    texSubdataDesc.format = gapi::PixelFormat::LUMINANCE_ALPHA;
    texSubdataDesc.type = core::ValueDataType::UBYTE;
    texSubdataDesc.pixels = bi.data;

    // image->getTexture()->setPixelStorage(gapi::PixelStorageMode::UNPACK_ALIGNMENT, 1);
    // image->getTexture()->setPixelStorage(gapi::PixelStorageMode::UNPACK_ROW_LENGTH, bi.pitch);
    image->getTexture()->updateSubdata(texSubdataDesc);
    // image->getTexture()->setPixelStorage(gapi::PixelStorageMode::UNPACK_ROW_LENGTH, 0);

    font_->cache_[font_->glyphs_[i].code].rect = math::rect4f_t(pos.getX() / (f32_t)font_->getAtlasSize().getW(),
        pos.getY() / (f32_t)font_->getAtlasSize().getH(),
        (pos.getX() + font_->maxSize_.getW()) / (f32_t)font_->getAtlasSize().getW(),
        (pos.getY() + font_->maxSize_.getH()) / (f32_t)font_->getAtlasSize().getH());

    auto posx = pos.getX() + font_->maxSize_.getW();
    pos.setX(posx);

    if (font_->maxSize_.getH() > maxCharTall) {
      maxCharTall = font_->maxSize_.getH();
    }
  }

  auto shape = new render::procedurals::prims::Quadrilateral<math::VertexTexCoord>(
      {gapi::VertexSemantic::POS, gapi::VertexSemantic::COL, gapi::VertexSemantic::TEXCOORD_0});

  shape->setPosDataAttrib(math::rect4f_t(-0.3F, -0.3F, 0.3F, 0.3F));
  shape->setColDataAttrib(COL4F_WHITE);
  shape->setTexDataAttrib(math::rect4f_t(0.0F, 0.0F, 1.0F, 1.0F));

  render::GeometryCreateInfo atlasGeomCreateInfo;
  atlasGeomCreateInfo.indexed = true;
  atlasGeomCreateInfo.topology = gapi::TopologyType::TRIANGLE_LIST;
  atlasGeomCreateInfo.bo[render::Constants::IDX_VBO].desc.usage = gapi::BufferUsage::STATIC;
  atlasGeomCreateInfo.bo[render::Constants::IDX_VBO].desc.byteStride = sizeof(math::VertexTexCoord);
  atlasGeomCreateInfo.bo[render::Constants::IDX_VBO].desc.capacity = 4;
  auto dataa = new f32_t[4 * sizeof(math::VertexTexCoord)];
  shape->data()->getVertices(dataa, 0, 4);
  atlasGeomCreateInfo.bo[render::Constants::IDX_VBO].data = dataa;
  std::cout << math::vec3f_t(dataa[0], dataa[1], dataa[2]) << std::endl;
  std::cout << math::vec3f_t(dataa[9], dataa[10], dataa[11]) << std::endl;

  atlasGeomCreateInfo.bo[render::Constants::IDX_EBO].desc.usage = gapi::BufferUsage::STATIC;
  atlasGeomCreateInfo.bo[render::Constants::IDX_EBO].desc.byteStride = sizeof(u32_t);
  atlasGeomCreateInfo.bo[render::Constants::IDX_EBO].desc.capacity = 6;
  atlasGeomCreateInfo.bo[render::Constants::IDX_EBO].data = shape->data()->getElements();

  atlasGeomUid_ = subsystem->getGeomBuilder()
                      ->create(3, atlasGeomCreateInfo, shape->getVertexAttribs(), textMtrl_->getEffect())
                      .value();

  // --------------

  rectGeomDataDivisor_ =
      new render::GeomInstanceDataDivisor<render::procedurals::prims::Quadrilateral<math::VertexColor>>(
          render::Constants::MAX_NUM_INSTANCES);

  rectGeomDataDivisor_->addInstanceData({gapi::VertexSemantic::POS, gapi::VertexSemantic::COL});
  rectGeomDataDivisor_->addInstanceData({gapi::VertexSemantic::POS, gapi::VertexSemantic::COL});
  rectGeomDataDivisor_->addInstanceData({gapi::VertexSemantic::POS, gapi::VertexSemantic::COL});

  render::GeometryCreateInfo rectGeomCreateInfo;
  rectGeomCreateInfo.indexed = true;
  rectGeomCreateInfo.topology = gapi::TopologyType::TRIANGLE_LIST;
  rectGeomCreateInfo.bo[render::Constants::IDX_VBO].desc.usage = gapi::BufferUsage::DYNAMIC;
  rectGeomCreateInfo.bo[render::Constants::IDX_VBO].desc.byteStride = sizeof(math::VertexColor);
  rectGeomCreateInfo.bo[render::Constants::IDX_VBO].desc.capacity = 4 * rectGeomDataDivisor_->getInstSize();
  rectGeomCreateInfo.bo[render::Constants::IDX_VBO].data = nullptr;

  rectGeomCreateInfo.bo[render::Constants::IDX_EBO].desc.usage = gapi::BufferUsage::STATIC;
  rectGeomCreateInfo.bo[render::Constants::IDX_EBO].desc.byteStride = sizeof(u32_t);
  auto rectIdxs = rectGeomDataDivisor_->getIndices<MAX_UI_RECT>();
  rectGeomCreateInfo.bo[render::Constants::IDX_EBO].desc.capacity = rectIdxs.size();
  rectGeomCreateInfo.bo[render::Constants::IDX_EBO].data = rectIdxs.data();

  // for (auto i = 0; i < rectGeomCreateInfo.bo[render::Constants::IDX_EBO].desc.capacity; ++i) {
  //   std::cout << i << " = " << ((u32_t *)rectGeomCreateInfo.bo[render::Constants::IDX_EBO].data)[i] << std::endl;
  // }

  subsystem->getGeomBuilder()->createInstance<render::procedurals::prims::Quadrilateral<math::VertexColor>>(
      0 /* rect */, rectGeomDataDivisor_, rectGeomCreateInfo, rectMtrl_->getEffect());

  // --------------

  textGeomDataDivisor_ =
      new render::GeomInstanceDataDivisor<render::procedurals::prims::Quadrilateral<math::VertexTexCoord>>(
          render::Constants::MAX_NUM_INSTANCES);

  textGeomDataDivisor_->addInstanceData(
      {gapi::VertexSemantic::POS, gapi::VertexSemantic::COL, gapi::VertexSemantic::TEXCOORD_0});
  textGeomDataDivisor_->addInstanceData(
      {gapi::VertexSemantic::POS, gapi::VertexSemantic::COL, gapi::VertexSemantic::TEXCOORD_0});
  textGeomDataDivisor_->addInstanceData(
      {gapi::VertexSemantic::POS, gapi::VertexSemantic::COL, gapi::VertexSemantic::TEXCOORD_0});
  textGeomDataDivisor_->addInstanceData(
      {gapi::VertexSemantic::POS, gapi::VertexSemantic::COL, gapi::VertexSemantic::TEXCOORD_0});
  textGeomDataDivisor_->addInstanceData(
      {gapi::VertexSemantic::POS, gapi::VertexSemantic::COL, gapi::VertexSemantic::TEXCOORD_0});

  render::GeometryCreateInfo textGeomCreateInfo;
  textGeomCreateInfo.indexed = true;
  textGeomCreateInfo.topology = gapi::TopologyType::TRIANGLE_LIST;
  textGeomCreateInfo.bo[render::Constants::IDX_VBO].desc.usage = gapi::BufferUsage::DYNAMIC;
  textGeomCreateInfo.bo[render::Constants::IDX_VBO].desc.byteStride = sizeof(math::VertexTexCoord);
  textGeomCreateInfo.bo[render::Constants::IDX_VBO].desc.capacity = 4 * textGeomDataDivisor_->getInstSize();
  textGeomCreateInfo.bo[render::Constants::IDX_VBO].data = nullptr;

  textGeomCreateInfo.bo[render::Constants::IDX_EBO].desc.usage = gapi::BufferUsage::STATIC;
  textGeomCreateInfo.bo[render::Constants::IDX_EBO].desc.byteStride = sizeof(u32_t);
  auto textIdxs = textGeomDataDivisor_->getIndices<MAX_UI_TEXT>();
  textGeomCreateInfo.bo[render::Constants::IDX_EBO].desc.capacity = textIdxs.size();
  textGeomCreateInfo.bo[render::Constants::IDX_EBO].data = textIdxs.data();

  // for (auto i = 0; i < textGeomCreateInfo.bo[render::Constants::IDX_EBO].desc.capacity; ++i) {
  //   std::cout << i << " = " << ((u32_t *)textGeomCreateInfo.bo[render::Constants::IDX_EBO].data)[i] << std::endl;
  // }

  textId_ = subsystem->getGeomBuilder()
                ->createInstance<render::procedurals::prims::Quadrilateral<math::VertexTexCoord>>(
                    1 /* text */, textGeomDataDivisor_, textGeomCreateInfo, textMtrl_->getEffect())
                .value();

  // --------------

  debugGeomDataDivisor_ = new render::GeomInstanceDataDivisor<render::procedurals::guides::Line<math::VertexColor>>(
      render::Constants::MAX_NUM_INSTANCES);

  debugGeomDataDivisor_->addInstanceData({gapi::VertexSemantic::POS, gapi::VertexSemantic::COL});
  debugGeomDataDivisor_->addInstanceData({gapi::VertexSemantic::POS, gapi::VertexSemantic::COL});
  debugGeomDataDivisor_->addInstanceData({gapi::VertexSemantic::POS, gapi::VertexSemantic::COL});
  debugGeomDataDivisor_->addInstanceData({gapi::VertexSemantic::POS, gapi::VertexSemantic::COL});
  debugGeomDataDivisor_->addInstanceData({gapi::VertexSemantic::POS, gapi::VertexSemantic::COL});

  // debugGeomDataDivisor_->addInstanceData({gapi::VertexSemantic::POS, gapi::VertexSemantic::COL});
  // debugGeomDataDivisor_->addInstanceData({gapi::VertexSemantic::POS, gapi::VertexSemantic::COL});
  // debugGeomDataDivisor_->addInstanceData({gapi::VertexSemantic::POS, gapi::VertexSemantic::COL});
  // debugGeomDataDivisor_->addInstanceData({gapi::VertexSemantic::POS, gapi::VertexSemantic::COL});
  // debugGeomDataDivisor_->addInstanceData({gapi::VertexSemantic::POS, gapi::VertexSemantic::COL});

  render::GeometryCreateInfo debugGeomCreateInfo;
  debugGeomCreateInfo.indexed = false;
  debugGeomCreateInfo.topology = gapi::TopologyType::LINE_LIST;
  debugGeomCreateInfo.bo[render::Constants::IDX_VBO].desc.usage = gapi::BufferUsage::DYNAMIC;
  debugGeomCreateInfo.bo[render::Constants::IDX_VBO].desc.byteStride = sizeof(math::VertexColor);
  debugGeomCreateInfo.bo[render::Constants::IDX_VBO].desc.capacity = 5 * debugGeomDataDivisor_->getInstSize();
  debugGeomCreateInfo.bo[render::Constants::IDX_VBO].data = nullptr;

  subsystem->getGeomBuilder()->createInstance<render::procedurals::guides::Line<math::VertexColor>>(
      2 /* debug */, debugGeomDataDivisor_, debugGeomCreateInfo, rectMtrl_->getEffect());

  auto geoms = subsystem->getGeomBuilder()->getGeometries();
  rectGeom_ =
      static_cast<render::GeomInstance<render::procedurals::prims::Quadrilateral<math::VertexColor>> *>(geoms[0]);
  textGeom_ =
      static_cast<render::GeomInstance<render::procedurals::prims::Quadrilateral<math::VertexTexCoord>> *>(geoms[1]);
  debugGeom_ = static_cast<render::GeomInstance<render::procedurals::guides::Line<math::VertexColor>> *>(geoms[2]);
  atlasGeom_ = subsystem->getGeomBuilder()->find(atlasGeomUid_);
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
  chunk.rect.color = col;
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
  chunk.text.color = col;
  chunk.text.text = text;
}

void Painter::onUpdateBatchChunks() {
  const auto wdt = font_->getAtlasSize().getW() / font_->maxSize_.getW();
  const auto hdt = font_->getAtlasSize().getH() / font_->maxSize_.getH();

  auto nextRectIdx = 0;
  auto nextTextIdx = 0;
  auto nextDebugIdx = 0;

  for (auto chunkIndex = 0; chunkIndex < geomBatchChunkSize_; ++chunkIndex) {
    const GeometryBatchChunk &chunk = geomBatchChunks_[chunkIndex];

    if (chunk.type == GeometryBatchChunkType::RECT) {
      if (rectGeom_) {
        auto inst = rectGeom_->getDivisor()->at(nextRectIdx);
        if (!inst) {
          std::cout << "[ERR]: Inst" << std::endl;
        } else {
          inst->update(math::rect4f_t(chunk.rect.x, chunk.rect.y, chunk.rect.w, chunk.rect.h), chunk.rect.color);
          nextRectIdx += 1;
        }
      }
    } else if (chunk.type == GeometryBatchChunkType::TEXT) {
      auto pos = math::point2f_t(chunk.text.x, chunk.text.y);
      // auto size = math::size2f_t(chunk.text.w, chunk.text.h);

      for (auto i = 0; i < strlen(chunk.text.text); ++i) {
        auto info = font_->getCharInfo(chunk.text.text[i]);
        if (info.has_value()) {
          // auto symidx = info.value().symidx;
          // const auto x = symidx % wdt;
          // const auto y = symidx / hdt;

          auto size = info.value().size;
          auto tlTop = info.value().tl.getX() / static_cast<f32_t>(font_->getAtlasSize().getW());
          auto tlLft = info.value().tl.getY() / static_cast<f32_t>(font_->getAtlasSize().getH());
          auto bearing = info.value().bearing;
          auto advance = info.value().advance;

          auto msx = size.getW() / static_cast<f32_t>(font_->getAtlasSize().getW());
          auto msy = size.getH() / static_cast<f32_t>(font_->getAtlasSize().getH());

          auto scale = 0.5F;

          auto textPos = math::rect4f_t(pos.getX(), pos.getY(), pos.getX() + msx * scale,
              pos.getY() +
                  (msy + (info.value().bearing.getY() / static_cast<f32_t>(font_->getAtlasSize().getH()))) * scale);

          if (textGeom_) {
            auto inst = textGeom_->getDivisor()->at(nextTextIdx);
            if (!inst) {
              std::cout << "[ERR]: Inst" << std::endl;
            } else {
              inst->setPosDataAttrib(textPos);
              inst->setColDataAttrib(chunk.text.color);

              auto newRect = info.value().rect;
              auto mmx = font_->maxSize_.getW() / static_cast<f32_t>(font_->getAtlasSize().getW());
              auto ttx = info.value().size.getW() / static_cast<f32_t>(font_->getAtlasSize().getW());
              auto mmy = font_->maxSize_.getH() / static_cast<f32_t>(font_->getAtlasSize().getH());
              auto tty = info.value().size.getH() / static_cast<f32_t>(font_->getAtlasSize().getH());

              auto bby = info.value().bearing.getY() / static_cast<f32_t>(font_->getAtlasSize().getH());

              // std::cout << info.value().rect << " x "
              //           << (info.value().size.getW() / static_cast<f32_t>(font_->getAtlasSize().getW())) << " "
              //           << (info.value().size.getH() / static_cast<f32_t>(font_->getAtlasSize().getH())) <<
              //           std::endl;

              newRect.setR(info.value().rect.getR() - (mmx - ttx));
              newRect.setB(info.value().rect.getB() - (mmy - tty));  // + (tty - bby));
              inst->setTexDataAttrib(newRect);
              nextTextIdx += 1;
            }
          }

          if (debugGeom_) {
            auto inst = debugGeom_->getDivisor()->at(nextDebugIdx);
            // auto inst2 = debugGeom_->getDivisor()->at(nextDebugIdx + 1);
            if (!inst) {
              std::cout << "[ERR]: Inst" << std::endl;
            } else {
              inst->setPosDataAttrib(math::vec3f_t(textPos.getL(), textPos.getT(), 0.0F),
                  math::vec3f_t(textPos.getL(), textPos.getB(), 0.0F));

              inst->setPosDataAttrib2(math::vec3f_t(textPos.getR(), textPos.getT(), 0.0F),
                  math::vec3f_t(textPos.getR(), textPos.getB(), 0.0F));

              inst->setColDataAttrib(COL4F_RED);

              // inst2->setPosDataAttrib(math::vec3f_t(textPos.getL(), textPos.getB(), 0.0F),
              //     math::vec3f_t(textPos.getR(), textPos.getB(), 0.0F));
              // inst2->setColDataAttrib(COL4F_BLUE);

              nextDebugIdx += 1;
            }
          }

          pos.setX(pos.getX() + msx * scale);
        }
      }
    }
  }

  if (rectGeom_) {
    rectGeom_->remap();
  }

  if (textGeom_) {
    textGeom_->remap();
  }

  if (debugGeom_) {
    debugGeom_->remap();
  }
}

void Painter::onUpdate(math::mat4f_t tfrm, math::mat4f_t proj, math::mat4f_t view, f32_t dtime) {
  this->onUpdateBatchChunks();

  geomBatchChunkSize_ = 0;

  render::pipeline::ForwardRenderCommand textCmd;
  if (textGeom_) {
    textCmd.stage = 0;
    textCmd.blendDesc.enabled = true;
    textCmd.blendDesc.src = gapi::BlendFn::SRC_ALPHA;
    textCmd.blendDesc.dst = gapi::BlendFn::ONE_MINUS_SRC_ALPHA;
    textCmd.blendDesc.mask = true;
    textCmd.rasterizerDesc.mode = gapi::CullFace::BACK;
    textCmd.rasterizerDesc.ccw = false;
    textCmd.depthDesc.enabled = true;
    textCmd.depthDesc.func = gapi::CompareFn::LESS;
    textCmd.depthDesc.mask = true;
    textCmd.depthDesc.near = 0;
    textCmd.depthDesc.far = 0;
    textCmd.stencilDesc.enabled = true;
    textCmd.stencilDesc.front.func = gapi::CompareFn::ALWAYS;
    textCmd.stencilDesc.front.fail = gapi::StencilOp::KEEP;
    textCmd.stencilDesc.front.depthFail = gapi::StencilOp::KEEP;
    textCmd.stencilDesc.front.depthPass = gapi::StencilOp::REPLACE;
    textCmd.stencilDesc.front.rmask = 0xFFFFFF;
    textCmd.stencilDesc.front.wmask = textCmd.stencilDesc.front.rmask;
    textCmd.stencilDesc.front.reference = 1;
    textCmd.stencilDesc.back = textCmd.stencilDesc.front;
    // textCmd.geometry = textGeom_;
    textCmd.geom = textGeom_;
    textCmd.topology = gapi::TopologyType::TRIANGLE_LIST;
    textCmd.material = textMtrl_;
    textCmd.tfrm = tfrm;
    textCmd.proj = proj;
    textCmd.view = math::mat4f_t();  // view;

    subqueue_->post(textCmd);
  }

  render::pipeline::ForwardRenderCommand rectCmd;
  if (rectGeom_) {
    rectCmd.stage = 0;
    rectCmd.blendDesc.enabled = false;
    rectCmd.blendDesc.src = gapi::BlendFn::SRC_ALPHA;
    rectCmd.blendDesc.dst = gapi::BlendFn::ONE_MINUS_SRC_ALPHA;
    rectCmd.blendDesc.mask = true;
    rectCmd.rasterizerDesc.mode = gapi::CullFace::BACK;
    rectCmd.rasterizerDesc.ccw = false;
    rectCmd.depthDesc.enabled = true;
    rectCmd.depthDesc.func = gapi::CompareFn::LESS;
    rectCmd.depthDesc.mask = true;
    rectCmd.depthDesc.near = 0;
    rectCmd.depthDesc.far = 0;
    rectCmd.stencilDesc.enabled = true;
    rectCmd.stencilDesc.front.func = gapi::CompareFn::ALWAYS;
    rectCmd.stencilDesc.front.fail = gapi::StencilOp::KEEP;
    rectCmd.stencilDesc.front.depthFail = gapi::StencilOp::KEEP;
    rectCmd.stencilDesc.front.depthPass = gapi::StencilOp::REPLACE;
    rectCmd.stencilDesc.front.rmask = 0xFFFFFF;
    rectCmd.stencilDesc.front.wmask = rectCmd.stencilDesc.front.rmask;
    rectCmd.stencilDesc.front.reference = 1;
    rectCmd.stencilDesc.back = rectCmd.stencilDesc.front;
    rectCmd.topology = gapi::TopologyType::TRIANGLE_LIST;
    rectCmd.geom = rectGeom_;
    rectCmd.material = rectMtrl_;
    rectCmd.tfrm = tfrm;
    rectCmd.proj = proj;
    // rectCmd.proj.setData(math::Projection(
    //     (struct math::ProjectionDescription){.rect = {{-0.5F /* L */, -0.5F /* T */, 0.5F /* R */, 0.5F /* B */}},
    //         .fov = 0,
    //         .aspect = f32_t(800 / 600),
    //         .znear = -1.0F,
    //         .zfar = 1.0F})
    //                          .makeOrtho());

    rectCmd.view = math::mat4f_t();

    subqueue_->post(rectCmd);
  }

  render::pipeline::ForwardRenderCommand debugCmd;
  if (debugGeom_) {
    debugCmd.stage = 0;
    debugCmd.blendDesc.enabled = true;
    debugCmd.blendDesc.src = gapi::BlendFn::SRC_ALPHA;
    debugCmd.blendDesc.dst = gapi::BlendFn::ONE_MINUS_SRC_ALPHA;
    debugCmd.blendDesc.mask = true;
    debugCmd.rasterizerDesc.mode = gapi::CullFace::BACK;
    debugCmd.rasterizerDesc.ccw = false;
    debugCmd.depthDesc.enabled = true;
    debugCmd.depthDesc.func = gapi::CompareFn::LESS;
    debugCmd.depthDesc.mask = true;
    debugCmd.depthDesc.near = 0;
    debugCmd.depthDesc.far = 0;
    debugCmd.stencilDesc.enabled = true;
    debugCmd.stencilDesc.front.func = gapi::CompareFn::ALWAYS;
    debugCmd.stencilDesc.front.fail = gapi::StencilOp::KEEP;
    debugCmd.stencilDesc.front.depthFail = gapi::StencilOp::KEEP;
    debugCmd.stencilDesc.front.depthPass = gapi::StencilOp::REPLACE;
    debugCmd.stencilDesc.front.rmask = 0xFFFFFF;
    debugCmd.stencilDesc.front.wmask = debugCmd.stencilDesc.front.rmask;
    debugCmd.stencilDesc.front.reference = 1;
    debugCmd.stencilDesc.back = debugCmd.stencilDesc.front;
    // debugCmd.geometry = textGeom_;
    debugCmd.geom = debugGeom_;
    debugCmd.topology = gapi::TopologyType::LINE_LIST;
    debugCmd.material = rectMtrl_;
    debugCmd.tfrm = tfrm;
    debugCmd.proj = rectCmd.proj;
    debugCmd.view = math::mat4f_t();  // view;

    subqueue_->post(debugCmd);
  }

  render::pipeline::ForwardRenderCommand atlasCmd;
  if (atlasGeom_) {
    atlasCmd.stage = 0;
    atlasCmd.blendDesc.enabled = true;
    atlasCmd.blendDesc.src = gapi::BlendFn::SRC_ALPHA;
    atlasCmd.blendDesc.dst = gapi::BlendFn::ONE_MINUS_SRC_ALPHA;
    atlasCmd.blendDesc.mask = true;
    atlasCmd.rasterizerDesc.mode = gapi::CullFace::BACK;
    atlasCmd.rasterizerDesc.ccw = false;
    atlasCmd.depthDesc.enabled = true;
    atlasCmd.depthDesc.func = gapi::CompareFn::LESS;
    atlasCmd.depthDesc.mask = true;
    atlasCmd.depthDesc.near = 0;
    atlasCmd.depthDesc.far = 0;
    atlasCmd.stencilDesc.enabled = true;
    atlasCmd.stencilDesc.front.func = gapi::CompareFn::ALWAYS;
    atlasCmd.stencilDesc.front.fail = gapi::StencilOp::KEEP;
    atlasCmd.stencilDesc.front.depthFail = gapi::StencilOp::KEEP;
    atlasCmd.stencilDesc.front.depthPass = gapi::StencilOp::REPLACE;
    atlasCmd.stencilDesc.front.rmask = 0xFFFFFF;
    atlasCmd.stencilDesc.front.wmask = atlasCmd.stencilDesc.front.rmask;
    atlasCmd.stencilDesc.front.reference = 1;
    atlasCmd.stencilDesc.back = atlasCmd.stencilDesc.front;
    // debugCmd.geometry = textGeom_;
    atlasCmd.geom = atlasGeom_;
    atlasCmd.topology = gapi::TopologyType::TRIANGLE_LIST;
    atlasCmd.material = textMtrl_;
    atlasCmd.tfrm = tfrm;
    atlasCmd.proj = rectCmd.proj;
    atlasCmd.view = math::mat4f_t();  // view;

    subqueue_->post(atlasCmd);
  }
}

NAMESPACE_END(ui)
NAMESPACE_END(sway)
