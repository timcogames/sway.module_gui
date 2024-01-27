#include <sway/ui.hpp>

#include <gtest/gtest.h>

#include <memory>

using namespace sway;

TEST(FontTest, Ctor) {
  auto font = std::make_shared<ui::ft2::Font>();
  ASSERT_TRUE(font != nullptr);
}
