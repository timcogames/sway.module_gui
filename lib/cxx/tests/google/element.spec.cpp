#include <sway/math.hpp>
#include <sway/ui.hpp>

#undef Bool
#undef None

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>
#include <utility>

using namespace sway;

TEST(ElementTest, ctor_def) {
  ui::Element elem;

  ASSERT_EQ(elem.getPosition(), ui::ElementPosition::RELATIVE);
  ASSERT_EQ(elem.getOffset(), math::point2f_zero);
  ASSERT_FALSE(elem.isOffsetDirty());
}

TEST(ElementTest, position) {
  ui::Element elem;

  elem.setPosition(ui::ElementPosition::ABSOLUTE);
  ASSERT_EQ(elem.getPosition(), ui::ElementPosition::ABSOLUTE);
}

TEST(ElementTest, offset) {
  ui::Element elem;

  elem.setPosition(ui::ElementPosition::ABSOLUTE);
  elem.setOffset(1.0F, 2.0F);
  ASSERT_TRUE(elem.isOffsetDirty());

  elem.updateOffset();
  ASSERT_EQ(elem.getOffset(), math::point2f_t(1.0F, 2.0F));
}
