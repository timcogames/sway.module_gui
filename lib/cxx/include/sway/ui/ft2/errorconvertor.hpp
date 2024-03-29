#ifndef SWAY_UI_FT2_ERRORCONVERTOR_HPP
#define SWAY_UI_FT2_ERRORCONVERTOR_HPP

#include <sway/core.hpp>

#include <freetype/fttypes.h>
#include FT_FREETYPE_H

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(ft2)

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

NAMESPACE_END(ft2)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_FT2_ERRORCONVERTOR_HPP
