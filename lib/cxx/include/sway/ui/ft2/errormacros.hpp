#ifndef SWAY_UI_FT2_ERRORMACROS_HPP
#define SWAY_UI_FT2_ERRORMACROS_HPP

#include <sway/core.hpp>
#include <sway/ui/ft2/errorconvertor.hpp>

#include <freetype/fttypes.h>
#include <stdio.h>

NS_BEGIN_SWAY()
NS_BEGIN(ui)
NS_BEGIN(ft2)

#define CHECK_RESULT(error)                                                                 \
  ({                                                                                        \
    auto result = (error == FT_Err_Ok);                                                     \
    if (!result) {                                                                          \
      fprintf(stderr, "FT_Error (code 0x%02x) : %s\n", error, ErrorConvertor::conv(error)); \
      false;                                                                                \
    }                                                                                       \
    true;                                                                                   \
  })

NS_END()  // namespace ft2
NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_FT2_ERRORMACROS_HPP
