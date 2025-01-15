#ifndef SWAY_UI_FT2_ERRORMACROS_HPP
#define SWAY_UI_FT2_ERRORMACROS_HPP

#include <sway/ui/_stdafx.hpp>
#include <sway/ui/ft2/errorconvertor.hpp>

namespace sway::ui {

#define CHECK_RESULT(error)                                                                 \
  ({                                                                                        \
    auto result = (error == FT_Err_Ok);                                                     \
    if (!result) {                                                                          \
      fprintf(stderr, "FT_Error (code 0x%02x) : %s\n", error, ErrorConvertor::conv(error)); \
      false;                                                                                \
    }                                                                                       \
    true;                                                                                   \
  })

}  // namespace sway::ui

#endif  // SWAY_UI_FT2_ERRORMACROS_HPP
