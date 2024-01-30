#include <sway/ui/painter.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

template <typename TVertexDataType>
class Plane : public render::procedurals::Shape {
public:
  Plane(const math::size2f_t &size, const math::size2i_t &subdivisions, const math::col4f_t &col = COL4F_WHITE)
      : data_(std::make_shared<render::GeometryIndexedVertexData<TVertexDataType>>(
            4 * subdivisions.getW() * subdivisions.getH())) {
    auto sizeHalf = size / 2.0F;

    render::GeometryVertexAttribSet attribs = {
        .pos = data_->template createVertexAttrib<math::vec3f_t>(gapi::VertexSemantic::POS),
        .col = data_->template createVertexAttrib<math::vec4f_t>(gapi::VertexSemantic::COL),
        .tex = data_->template createVertexAttrib<math::vec2f_t>(gapi::VertexSemantic::TEXCOORD_0)};

    auto unitScale = 1.5F;
    auto tileWt = size.getW() * unitScale;
    auto tileHt = size.getH() * unitScale;

    u32_t tileCount = 0;

    for (auto y = 0; y < subdivisions.getH(); y++) {
      for (auto x = 0; x < subdivisions.getW(); x++) {
        attribs.pos->addVtxData({(0.0F + (f32_t)x) * tileWt, (0.0F + (f32_t)y) * tileHt, 0.0F});
        attribs.pos->addVtxData({(1.0F + (f32_t)x) * tileWt, (0.0F + (f32_t)y) * tileHt, 0.0F});
        attribs.pos->addVtxData({(0.0F + (f32_t)x) * tileWt, (1.0F + (f32_t)y) * tileHt, 0.0F});
        attribs.pos->addVtxData({(1.0F + (f32_t)x) * tileWt, (1.0F + (f32_t)y) * tileHt, 0.0F});

        attribs.col->addVtxData(col.toVec4());
        attribs.col->addVtxData(col.toVec4());
        attribs.col->addVtxData(col.toVec4());
        attribs.col->addVtxData(col.toVec4());

        attribs.tex->addVtxData(math::vec2f_t(1.0F, 1.0F));
        attribs.tex->addVtxData(math::vec2f_t(0.0F, 1.0F));
        attribs.tex->addVtxData(math::vec2f_t(1.0F, 0.0F));
        attribs.tex->addVtxData(math::vec2f_t(0.0F, 0.0F));

        data_->addTriIndices(0 + (tileCount * 4), 2 + (tileCount * 4), 1 + (tileCount * 4));
        data_->addTriIndices(1 + (tileCount * 4), 2 + (tileCount * 4), 3 + (tileCount * 4));

        tileCount++;
      }
    }
  }

  virtual ~Plane() = default;

  [[nodiscard]]
  auto getGeometryData() const -> render::GeometryDataPtr<TVertexDataType> {
    return data_;
  }

  template <std::size_t TSize>
  void useVertexSemanticSet(std::array<sway::gapi::VertexSemantic, TSize> &arr) {
    data_->useVertexSemanticSet(arr);
  }

  // clang-format off
  MTHD_OVERRIDE(auto getVertexAttribs() const -> render::VertexAttribMap_t) {  // clang-format on
    return data_->getAttribs();
  }

  // clang-format off
  MTHD_OVERRIDE(auto getVertexAttrib(gapi::VertexSemantic semantic) const -> render::VertexAttribPtr_t) {  // clang-format on
    return data_->getAttrib(semantic);
  }

  // clang-format off
  MTHD_OVERRIDE(auto getGeometryInfo() const -> render::GeometryCreateInfo) {  // clang-format on
    render::GeometryCreateInfo info;

    info.topology = gapi::TopologyType::TRIANGLE_LIST;
    info.vb.desc.usage = gapi::BufferUsage::DYNAMIC;
    info.vb.desc.byteStride = sizeof(TVertexDataType);
    info.vb.desc.capacity = data_->getVtxCount();
    info.vb.data = data_->getVtxRawdata();

    info.ib.desc.usage = gapi::BufferUsage::DYNAMIC;
    info.ib.desc.byteStride = sizeof(u32_t);
    info.ib.desc.capacity = data_->getIdxCount();
    info.ib.data = data_->getIndices().data();

    return info;
  }

  // clang-format off
  MTHD_OVERRIDE(auto getVertices() -> void *) {  // clang-format on
    return data_->getVtxRawdata();
  }

private:
  render::GeometryDataPtr<TVertexDataType> data_;
};

Painter::Painter()
    : geometry_(nullptr) {}

void Painter::initialize(std::shared_ptr<render::RenderSubsystem> subsystem,
    std::shared_ptr<render::MaterialManager> materialMngr, std::shared_ptr<rms::ImageResourceManager> imgResMngr,
    std::shared_ptr<rms::GLSLResourceManager> glslResMngr) {
  subqueue_ = subsystem->getQueueByIdx(0)->getSubqueues(render::RenderSubqueueGroup::OPAQUE)[0];

  material_ = std::make_shared<render::Material>("material_ui", imgResMngr, glslResMngr);
  material_->addImage("myimg1", "diffuse_sampler");
  material_->addEffect({"ui_vs", "ui_fs"});
  materialMngr->addMaterial(material_);

  std::array<gapi::VertexSemantic, 3> semantics = {
      gapi::VertexSemantic::POS, gapi::VertexSemantic::COL, gapi::VertexSemantic::TEXCOORD_0};

  auto shape = std::make_shared<Plane<math::VertexTexCoordEx>>(math::size2f_t(0.2F), math::size2i_t(1));
  shape->useVertexSemanticSet(semantics);

  geometry_ = std::make_shared<render::Geometry>(subsystem->getIdGenerator(), material_->getEffect(), true);
  geometry_->create(shape);
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
  cmd.geometry = geometry_;
  cmd.material = material_;
  cmd.tfrm = tfrm;
  cmd.proj = proj;
  cmd.view = view;

  subqueue_->post(cmd);
}

NAMESPACE_END(ui)
NAMESPACE_END(sway)
