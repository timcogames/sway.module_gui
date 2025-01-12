#ifndef SWAY_UI_FT2_ERRORCONVERTOR_HPP
#define SWAY_UI_FT2_ERRORCONVERTOR_HPP

#include <sway/core.hpp>

#include <freetype/fttypes.h>
#include FT_FREETYPE_H

namespace sway::ui {
NS_BEGIN(ft2)

struct ErrorConvertor {
  static auto conv(FT_Error error) -> lpcstr_t {
#undef FTERRORS_H_
#define FT_ERRORDEF(code, value, desc) \
  case code:                           \
    return desc;
#define FT_ERROR_START_LIST switch (error) {
#define FT_ERROR_END_LIST   \
  default:                  \
    return "Unknown error"; \
    }
#include FT_ERRORS_H
  }
};

NS_END()  // namespace ft2
}  // namespace sway::ui

#endif  // SWAY_UI_FT2_ERRORCONVERTOR_HPP
