#ifndef SWAY_UI_PAINTER_HPP
#define SWAY_UI_PAINTER_HPP

#include <sway/render/updatable.hpp>
#include <sway/ui/_stdafx.hpp>
#include <sway/ui/_typedefs.hpp>
#include <sway/ui/ft2/font.hpp>

#define GEOMERTY_BATCH_CHUNK_SIZE 5000

constexpr std::size_t MAX_UI_RECT = {20};
constexpr std::size_t MAX_UI_TEXT = {100};

namespace sway::ui {

enum class GeometryBatchChunkType : u32_t { RECT, TEXT, IMG };

struct GeometryBatchChunkRect {
  f32_t x, y, w, h;
  f32_t zindex;
  math::col4f_t color;
};

struct GeometryBatchChunkText {
  f32_t x, y, w, h;
  f32_t zindex;
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

class Painter : public render::RenderComponent, public render::FinalUpdatable {
  DECLARE_CLASS_METADATA(Painter, RenderComponent)

public:
#pragma region "Define aliases"
  /** \~english @name Define aliases */ /** \~russian @name Определение алиасов */
  /** @{ */

  using SharedPtr_t = PainterSharedPtr_t;

  /** @} */
#pragma endregion

#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  Painter();

  ~Painter();

  /** @} */
#pragma endregion

  void initialize(Font::SharedPtr_t font, render::RenderSubsystemSharedPtr_t subsys,
      render::MaterialManagerTypedefs::SharedPtr_t materialMngr, std::shared_ptr<rms::ImageResourceManager> imgResMngr,
      std::shared_ptr<rms::GLSLResourceManager> glslResMngr);

  void createRectGeom(render::RenderSubsystemSharedPtr_t subsys, u32_t geomIdx);

  void createTextGeom(render::RenderSubsystemSharedPtr_t subsys, u32_t geomIdx);

  void drawRect(f32_t x, f32_t y, f32_t w, f32_t h, math::col4f_t col, f32_t zindex = 0.0F);

  void drawRect(const math::rect4f_t &rect, math::col4f_t col, f32_t zindex = 0.0F);

  void drawText(f32_t x, f32_t y, f32_t w, f32_t h, math::col4f_t col, lpcstr_t text, f32_t zindex = 0.0F);

  void drawText(const math::rect4f_t &rect, math::col4f_t col, lpcstr_t text, f32_t zindex = 0.0F);

  void onUpdateBatchChunks();

#pragma region "Overridden RenderComponent methods"

  MTHD_OVERRIDE(void onUpdate(math::mat4f_t tfrm, math::mat4f_t proj, math::mat4f_t view, f32_t dtime));

#pragma endregion

#pragma region "Overridden FinalUpdatable methods"

  MTHD_OVERRIDE(void finalUpdate());

#pragma endregion

  void clear();

  auto getDefaultFont() -> Font::SharedPtr_t { return font_; }

  void setEnvironment(const core::Dictionary &env) { environment_ = env; }

  [[nodiscard]] auto getScreenWdt() -> f32_t { return (f32_t)environment_.getIntegerOrDefault("screen_wdt", 800); }

  [[nodiscard]] auto getScreenHgt() -> f32_t { return (f32_t)environment_.getIntegerOrDefault("screen_hgt", 600); }

  [[nodiscard]] auto getScreenSize() -> math::size2f_t { return math::size2f_t(getScreenWdt(), getScreenHgt()); }

  [[nodiscard]] auto getScreenHalfWdt() -> f32_t { return getScreenWdt() / 2.0F; }

  [[nodiscard]] auto getScreenHalfHgt() -> f32_t { return getScreenHgt() / 2.0F; }

private:
  core::Dictionary environment_;
  render::RenderQueueSharedPtr_t queue_;
  render::RenderSubqueueSharedPtr_t subqueue_;
  render::GeomBuilderTypedefs::SharedPtr_t geomBuilder_;

  render::MaterialTypedefs::SharedPtr_t rectMtrl_;
  render::GeomInstanceDataDivisor<render::procedurals::prims::Quadrilateral<math::VertexColor>> *rectGeomDataDivisor_;
  render::GeomInstance<render::procedurals::prims::Quadrilateral<math::VertexColor>> *rectGeom_;  // mapped

  render::MaterialTypedefs::SharedPtr_t textMtrl_;
  render::GeomInstanceDataDivisor<render::procedurals::prims::Quadrilateral<math::VertexTexCoord>>
      *textGeomDataDivisor_;
  render::GeomInstance<render::procedurals::prims::Quadrilateral<math::VertexTexCoord>> *textGeom_;

  u32_t rectId_;
  u32_t textId_;

  Font::SharedPtr_t font_;

  std::array<GeometryBatchChunk, GEOMERTY_BATCH_CHUNK_SIZE> geomBatchChunks_;
  u32_t geomBatchChunkSize_;

  int nextRectIdx_;
  int nextTextIdx_;
};

}  // namespace sway::ui

#endif  // SWAY_UI_PAINTER_HPP
