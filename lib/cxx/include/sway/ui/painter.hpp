#ifndef SWAY_UI_PAINTER_HPP
#define SWAY_UI_PAINTER_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render.hpp>
#include <sway/ui/ft2/font.hpp>

#include <array>
#include <memory>

#define GEOMERTY_BATCH_CHUNK_SIZE 5000

constexpr std::size_t MAX_UI_RECT = {3};
constexpr std::size_t MAX_UI_TEXT = {5};

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

enum class GeometryBatchChunkType : u32_t { RECT, TEXT, IMG };

struct GeometryBatchChunkRect {
  f32_t x, y, w, h;
  math::col4f_t color;
};

struct GeometryBatchChunkText {
  f32_t x, y, w, h;
  math::col4f_t color;
  lpcstr_t text;
};

struct GeometryBatchChunkImage {
  f32_t x, y, w, h;
  math::col4f_t color;
  std::shared_ptr<render::Image> image;
};

struct GeometryBatchChunk {
  GeometryBatchChunkType type;
  GeometryBatchChunkRect rect;
  GeometryBatchChunkText text;
  GeometryBatchChunkImage image;
};

class Painter : public render::RenderComponent {
public:
  DECLARE_CLASS_METADATA(Painter, RenderComponent)

  Painter();

  ~Painter();

  void initialize(std::shared_ptr<ft2::Font> font, std::shared_ptr<render::RenderSubsystem> subsystem,
      std::shared_ptr<render::MaterialManager> materialMngr, std::shared_ptr<rms::ImageResourceManager> imgResMngr,
      std::shared_ptr<rms::GLSLResourceManager> glslResMngr);

  void drawRect(f32_t x, f32_t y, f32_t w, f32_t h, math::col4f_t col);

  void drawText(f32_t x, f32_t y, f32_t w, f32_t h, math::col4f_t col, lpcstr_t text);

  void onUpdateBatchChunks();

  MTHD_OVERRIDE(void onUpdate(math::mat4f_t tfrm, math::mat4f_t proj, math::mat4f_t view, f32_t dtime));

  void clear() {
    // geomBuilder_->remove(1);
    // geomBuilder_->remove(0);
  }

private:
  std::shared_ptr<render::RenderQueue> queue_;
  std::shared_ptr<render::RenderSubqueue> subqueue_;

  std::string atlasGeomUid_;
  render::Geom *atlasGeom_;

  std::shared_ptr<render::Material> rectMtrl_;
  render::GeomInstanceDataDivisor<render::procedurals::prims::Quadrilateral<math::VertexColor>> *rectGeomDataDivisor_;
  render::GeomInstance<render::procedurals::prims::Quadrilateral<math::VertexColor>> *rectGeom_;  // mapped

  std::shared_ptr<render::Material> textMtrl_;
  render::GeomInstanceDataDivisor<render::procedurals::prims::Quadrilateral<math::VertexTexCoord>>
      *textGeomDataDivisor_;
  render::GeomInstance<render::procedurals::prims::Quadrilateral<math::VertexTexCoord>> *textGeom_;
  std::string textId_;

  render::GeomInstanceDataDivisor<render::procedurals::guides::Line<math::VertexColor>> *debugGeomDataDivisor_;
  render::GeomInstance<render::procedurals::guides::Line<math::VertexColor>> *debugGeom_;

  std::shared_ptr<ft2::Font> font_;

  std::array<GeometryBatchChunk, GEOMERTY_BATCH_CHUNK_SIZE> geomBatchChunks_;
  u32_t geomBatchChunkSize_;
};

NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_PAINTER_HPP
