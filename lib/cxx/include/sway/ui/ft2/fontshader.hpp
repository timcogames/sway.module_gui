#ifndef SWAY_UI_FT2_FONTSHADER_HPP
#define SWAY_UI_FT2_FONTSHADER_HPP

#include <sway/ui/_stdafx.hpp>
#include <sway/ui/typography.hpp>

namespace sway::ui {
NS_BEGIN(ft2)

class FontShader {
public:
  using Ptr_t = FontShader *;
  using SharedPtr_t = std::shared_ptr<FontShader>;

  FontShader() {}

  ~FontShader() = default;

  static void setColor(render::EffectTypedefs::Ptr_t eff, const typography::col_t &col) {
    eff->getShaderProgram()->setUniformCol4f("text_color", col);
  }

  static void setLayer(render::EffectTypedefs::Ptr_t eff, i32_t zindex) {
    eff->getShaderProgram()->setUniform1f("zindex", zindex == 0 ? -0.999F : (f32_t)(zindex - 100) / 100);
  }

private:
};

NS_END()  // namespace ft2
}  // namespace sway::ui

#endif  // SWAY_UI_FT2_FONTSHADER_HPP
