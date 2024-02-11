#ifndef SWAY_UI_FT2_ERRORMACROS_HPP
#define SWAY_UI_FT2_ERRORMACROS_HPP

#include <sway/core.hpp>
#include <sway/ui/ft2/errorconvertor.hpp>

#include <freetype/fttypes.h>
#include <stdio.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)
NAMESPACE_BEGIN(ft2)

#define CHECK_RESULT(error)                                                                 \
  ({                                                                                        \
    auto result = (error == FT_Err_Ok);                                                     \
    if (!result) {                                                                          \
      fprintf(stderr, "FT_Error (code 0x%02x) : %s\n", error, ErrorConvertor::conv(error)); \
      false;                                                                                \
    }                                                                                       \
    true;                                                                                   \
  })

NAMESPACE_END(ft2)
NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_FT2_ERRORMACROS_HPP
