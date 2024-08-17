#include <sway/ui.hpp>

#undef Bool
#undef None

#include <gtest/gtest.h>

#include <memory>

using namespace sway;

TEST(FontTest, ctor_def) {
  auto fontMngr = std::make_shared<ui::ft2::FontManager>();
  // fontMngr->load("array", "./assets/fonts/array.ttf");
  ASSERT_TRUE(fontMngr != nullptr);
}
