#include <sway/render/procedurals/prims/quadrilateral.hpp>
#include <sway/ui/painter.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

static int maxCharTall = 0;
static math::point2i_t pos;

Painter::Painter()
    : geomBatchChunkSize_(0) {}

Painter::~Painter() {}

void Painter::initialize(ft2::Font::SharedPtr_t font, std::shared_ptr<render::RenderSubsystem> subsystem,
    std::shared_ptr<render::MaterialManager> materialMngr, std::shared_ptr<rms::ImageResourceManager> imgResMngr,
    std::shared_ptr<rms::GLSLResourceManager> glslResMngr) {

  font_ = font;

  subqueue_ = std::make_shared<render::RenderSubqueue>();
  subqueue_->initialize();

  queue_ = subsystem->createQueue(core::detail::toBase(core::intrusive::Priority::VERY_HIGH));
  queue_->addSubqueue(subqueue_);

  subqueue_ = subsystem->getQueueByPriority(core::detail::toBase(core::intrusive::Priority::VERY_HIGH))
                  ->getSubqueues(render::RenderSubqueueGroup::OPAQUE)[0];

  const std::unordered_map<gapi::ShaderType, std::string> shaderSources = {
      {gapi::ShaderType::VERT, "layout (location = 0) in vec3 attrib_pos;"
                               "layout (location = 1) in vec4 attrib_col;"
                               "uniform mat4 mat_view_proj;"
                               "uniform mat4 mat_model;"
                               "out vec4 vtx_col;"
                               "void main() {"
                               "    gl_Position = mat_view_proj * mat_model * vec4(attrib_pos, 1.0);"
                               "    gl_Position.y = -gl_Position.y;"
                               "    vtx_col = attrib_col;"
                               "}"},
      {gapi::ShaderType::FRAG, "in vec4 vtx_col;"
                               "out vec4 out_col;"
                               "void main() {"
                               "    out_col = vtx_col;"
                               "}"}};

  rectMtrl_ = std::make_shared<render::Material>("material_ui_rect", imgResMngr, glslResMngr);
  rectMtrl_->addEffect(shaderSources);
  // rectMtrl_->addEffect({"ui_rect_vs", "ui_rect_fs"});
  materialMngr->addMaterial(rectMtrl_);

  textMtrl_ = std::make_shared<render::Material>("material_ui_text", imgResMngr, glslResMngr);
  textMtrl_->addEffect((std::array<std::string, 2>){"ui_text_vs", "ui_text_fs"});
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

  for (auto i = 0; i < font_->glyphs_.size(); i++) {
    auto bi = font_->getBitmapData(font_->glyphs_[i]);

    auto halfGlyphX = (font_->maxSize_.getW() - bi.bitmapSize.getW()) / 2;
    auto halfGlyphY = (font_->maxSize_.getH() - bi.bitmapSize.getH()) / 2;

    if (pos.getX() + font_->maxSize_.getW() > font_->getAtlasSize().getW()) {
      int newLineY = pos.getY() + maxCharTall;

      pos.set(0, newLineY);
      maxCharTall = 0;
    }

    gapi::TextureSubdataDescriptor texSubdataDesc;
    texSubdataDesc.level = 0;
    texSubdataDesc.offset = pos;
    texSubdataDesc.offset.setX(texSubdataDesc.offset.getX() + halfGlyphX);
    texSubdataDesc.offset.setY(texSubdataDesc.offset.getY() + halfGlyphY);
    texSubdataDesc.size = font_->maxSize_;
    texSubdataDesc.format = gapi::PixelFormat::LUMINANCE_ALPHA;
    texSubdataDesc.type = core::ValueDataType::UBYTE;
    texSubdataDesc.pixels = bi.data.get();

    image->getTexture()->updateSubdata(texSubdataDesc);

    // clang-format off
    font_->cache_[font_->glyphs_[i].code].rect = math::rect4f_t(
       texSubdataDesc.offset.getX() / (f32_t)font_->getAtlasSize().getW(),
       texSubdataDesc.offset.getY() / (f32_t)font_->getAtlasSize().getH(),
      (texSubdataDesc.offset.getX() + bi.bitmapSize.getW()) / (f32_t)font_->getAtlasSize().getW(),
      (texSubdataDesc.offset.getY() + bi.bitmapSize.getH()) / (f32_t)font_->getAtlasSize().getH());
    // clang-format on

    pos.setX(pos.getX() + font_->maxSize_.getW());

    if (font_->maxSize_.getH() > maxCharTall) {
      maxCharTall = font_->maxSize_.getH();
    }
  }

  geomBuilder_ = subsystem->getGeomBuilder();

  createRectGeom(subsystem, 0);
  createTextGeom(subsystem, 1);
}

void Painter::createRectGeom(std::shared_ptr<render::RenderSubsystem> subsystem, u32_t geomIdx) {
  rectGeomDataDivisor_ =
      new render::GeomInstanceDataDivisor<render::procedurals::prims::Quadrilateral<math::VertexColor>>(
          {gapi::VertexSemantic::POS, gapi::VertexSemantic::COL}, MAX_UI_RECT);

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

  geomBuilder_->createInstance<render::procedurals::prims::Quadrilateral<math::VertexColor>>(
      geomIdx, rectGeomDataDivisor_, rectGeomCreateInfo, rectMtrl_->getEffect());
}

void Painter::createTextGeom(std::shared_ptr<render::RenderSubsystem> subsystem, u32_t geomIdx) {
  textGeomDataDivisor_ =
      new render::GeomInstanceDataDivisor<render::procedurals::prims::Quadrilateral<math::VertexTexCoord>>(
          {gapi::VertexSemantic::POS, gapi::VertexSemantic::COL, gapi::VertexSemantic::TEXCOORD_0}, MAX_UI_TEXT);

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

  textId_ = geomBuilder_->createInstance<render::procedurals::prims::Quadrilateral<math::VertexTexCoord>>(
      geomIdx, textGeomDataDivisor_, textGeomCreateInfo, textMtrl_->getEffect());
}

void Painter::clear() {
  // geomBuilder_->remove(1);
  // geomBuilder_->remove(0);
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
  // chunk.text.w = w;
  // chunk.text.h = h;
  chunk.text.color = col;
  chunk.text.text = text;
}

void Painter::onUpdateBatchChunks() {
  nextRectIdx_ = 0;
  nextTextIdx_ = 0;

  for (auto chunkIndex = 0; chunkIndex < geomBatchChunkSize_; ++chunkIndex) {
    const GeometryBatchChunk &chunk = geomBatchChunks_[chunkIndex];

    if (chunk.type == GeometryBatchChunkType::RECT) {
      if (rectGeom_ != nullptr) {
        auto inst = rectGeom_->getDivisor()->at(nextRectIdx_);
        if (!inst) {
          std::cout << "[ERR]: Inst" << std::endl;
        } else {
          inst->setRemap(true);

          auto dX = 1.0F / ((f32_t)800 / 2.0F);
          auto dY = 1.0F / ((f32_t)600 / 2.0F);

          inst->setPosDataAttrib(
              math::rect4f_t(chunk.rect.x * dX, chunk.rect.y * dY, chunk.rect.w * dX, chunk.rect.h * dY));
          inst->setColDataAttrib(chunk.rect.color);
          nextRectIdx_ += 1;
        }
      }
    } else if (chunk.type == GeometryBatchChunkType::TEXT) {
      auto pos = math::point2f_t(chunk.text.x, chunk.text.y);

      for (auto i = 0; i < strlen(chunk.text.text); ++i) {
        auto charInfo = font_->getCharInfo(chunk.text.text[i]);
        if (!charInfo.has_value()) {
          return;
        }

        auto charSize = charInfo.value().size;
        auto charOffset = charInfo.value().bitmapGlyphOffset;

        auto xpos = pos.getX() + charOffset.getX();
        auto ypos = pos.getY() - charOffset.getY();
        auto w = xpos + static_cast<f32_t>(charSize.getW());
        auto h = ypos + static_cast<f32_t>(charSize.getH());

        auto textPos = math::rect4f_t(xpos, ypos, w, h);
        textPos.offset(0, font_->info_.height / 2);

        if (textGeom_ != nullptr) {
          auto inst = textGeom_->getDivisor()->at(nextTextIdx_);
          if (!inst) {
            std::cout << "[ERR]: Inst" << std::endl;
          } else {
            inst->setRemap(true);

            auto dX = 1.0F / ((f32_t)800 / 2.0F);
            auto dY = 1.0F / ((f32_t)600 / 2.0F);

            inst->setPosDataAttrib(
                math::rect4f_t(textPos.getL() * dX, textPos.getT() * dY, textPos.getR() * dX, textPos.getB() * dY));
            inst->setColDataAttrib(chunk.text.color);
            inst->setTexDataAttrib(charInfo.value().rect);
            nextTextIdx_ += 1;
          }
        }

        pos.setX(pos.getX() + static_cast<f32_t>(charInfo.value().advance));
      }
    }
  }

  if (rectGeom_ != nullptr) {
    rectGeom_->remap();
  }

  if (textGeom_ != nullptr) {
    textGeom_->remap();
  }
}

void Painter::onUpdate(math::mat4f_t tfrm, math::mat4f_t proj, math::mat4f_t view, f32_t dtime) {
  rectGeom_ = static_cast<render::GeomInstance<render::procedurals::prims::Quadrilateral<math::VertexColor>> *>(
      geomBuilder_->getGeometry(0));

  textGeom_ = static_cast<render::GeomInstance<render::procedurals::prims::Quadrilateral<math::VertexTexCoord>> *>(
      geomBuilder_->getGeometry(1));

  this->onUpdateBatchChunks();

  geomBatchChunkSize_ = 0;

  render::pipeline::ForwardRenderCommand rectCmd;
  if (rectGeom_ != nullptr) {
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
    rectCmd.tfrm = math::mat4f_t();
    // clang-format off
    rectCmd.proj.setData(math::Projection((struct math::ProjectionDescription) {
      .rect = {{ -1.0F /* L */, 1.0F /* B->T */, 1.0F /* R */, -1.0F /* T->B */ }},
      .fov = 0,
      .aspect = f32_t(800 / 600),
      .znear = 1.0F,
      .zfar = 10.0F
    }).makeOrtho());
    rectCmd.view = math::xform3f_t::translate(rectCmd.view, -1.0F, -1.0F, 0.0F);
    // clang-format on

    subqueue_->post(rectCmd);
  }

  render::pipeline::ForwardRenderCommand textCmd;
  if (textGeom_ != nullptr) {
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
    textCmd.geom = textGeom_;
    textCmd.topology = gapi::TopologyType::TRIANGLE_LIST;
    textCmd.material = textMtrl_;
    textCmd.tfrm = math::mat4f_t();
    // clang-format off
    textCmd.proj.setData(math::Projection((struct math::ProjectionDescription) {
      .rect = {{ -1.0F /* L */, 1.0F /* B->T */, 1.0F /* R */, -1.0F /* T->B */ }},
      .fov = 0,
      .aspect = f32_t(800 / 600),
      .znear = 1.0F,
      .zfar = 10.0F
    }).makeOrtho());
    textCmd.view = math::xform3f_t::translate(textCmd.view, -1.0F, -1.0F, 0.0F);
    // clang-format on

    subqueue_->post(textCmd);
  }

  this->finalUpdate();
}

void Painter::finalUpdate() {
  if (rectGeom_ != nullptr) {
    for (auto i = 0; i < rectGeom_->getDivisor()->getInstSize(); i++) {
      auto inst = rectGeom_->getDivisor()->at(i);
      if (!inst) {
        std::cout << "[ERR]: Inst" << std::endl;
      } else {
        inst->setRemap(false);
      }
    }
  }

  if (textGeom_ != nullptr) {
    for (auto i = 0; i < textGeom_->getDivisor()->getInstSize(); i++) {
      auto inst = textGeom_->getDivisor()->at(i);
      if (!inst) {
        std::cout << "[ERR]: Inst" << std::endl;
      } else {
        inst->setRemap(false);
      }
    }
  }
}

NAMESPACE_END(ui)
NAMESPACE_END(sway)
