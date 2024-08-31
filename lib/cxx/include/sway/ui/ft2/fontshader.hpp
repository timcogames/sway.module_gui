#ifndef SWAY_UI_FT2_FONTSHADER_HPP
#define SWAY_UI_FT2_FONTSHADER_HPP

#include <sway/core.hpp>
#include <sway/render.hpp>
#include <sway/ui/typography.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(ft2)

class FontShader {
public:
  using Ptr_t = FontShader *;
  using SharedPtr_t = std::shared_ptr<FontShader>;

  FontShader() {}

  ~FontShader() = default;

  static void setColor(render::EffectPtr_t eff, const typography::col_t &col) {
    eff->getShaderProgram()->setUniformCol4f("text_color", col);
  }

  static void setLayer(render::EffectPtr_t eff, i32_t zindex) {
    eff->getShaderProgram()->setUniform1f("zindex", zindex == 0 ? -0.999F : (f32_t)(zindex - 100) / 100);
  }

private:
};

NAMESPACE_END(ft2)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_FT2_FONTSHADER_HPP
