#ifndef SWAY_UI_PAINTER_HPP
#define SWAY_UI_PAINTER_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render.hpp>
#include <sway/ui/ft2/font.hpp>

#include <array>
#include <memory>

#define GEOMERTY_BATCH_CHUNK_SIZE 5000

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

enum class GeometryBatchChunkType : u32_t { RECT, TEXT, IMG };

struct GeometryBatchChunkRect {
  f32_t x, y, w, h;
  f32_t r, g, b, a;
};

struct GeometryBatchChunkText {
  f32_t x, y, w, h;
  f32_t r, g, b, a;
  lpcstr_t text;
};

struct GeometryBatchChunkImage {
  float x, y, w, h;
  float r, g, b, a;
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

  ~Painter() = default;

  void initialize(std::shared_ptr<ft2::Font> font, std::shared_ptr<render::RenderSubsystem> subsystem,
      std::shared_ptr<render::MaterialManager> materialMngr, std::shared_ptr<rms::ImageResourceManager> imgResMngr,
      std::shared_ptr<rms::GLSLResourceManager> glslResMngr);

  void drawRect(f32_t x, f32_t y, f32_t w, f32_t h, math::col4f_t col);

  void drawText(f32_t x, f32_t y, f32_t w, f32_t h, math::col4f_t col, lpcstr_t text);

  void onUpdateBatchChunks();

  MTHD_OVERRIDE(void onUpdate(math::mat4f_t tfrm, math::mat4f_t proj, math::mat4f_t view, f32_t dtime));

private:
  std::shared_ptr<render::RenderQueue> queue_;
  std::shared_ptr<render::RenderSubqueue> subqueue_;
  std::shared_ptr<render::Material> mtrl_;
  std::shared_ptr<render::PlaneArray<math::VertexTexCoordEx>> geomShape_;
  std::shared_ptr<render::Geometry> geom_;

  std::shared_ptr<ft2::Font> font_;

  std::array<GeometryBatchChunk, GEOMERTY_BATCH_CHUNK_SIZE> geomBatchChunks_;
  u32_t geomBatchChunkSize_;
};

NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_PAINTER_HPP
