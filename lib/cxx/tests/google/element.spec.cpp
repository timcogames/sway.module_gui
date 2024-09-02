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
  auto absElem = std::make_shared<ui::Element>();

  absElem->setPosition(ui::ElementPosition::ABSOLUTE);
  absElem->setOffset(1.0F, 2.0F);
  ASSERT_TRUE(absElem->isOffsetDirty());
  absElem->updateOffset();
  ASSERT_FALSE(absElem->isOffsetDirty());
  ASSERT_EQ(absElem->getOffset(), math::point2f_t(1.0F, 2.0F));

  auto relElem = std::make_shared<ui::Element>();
  relElem->setPosition(ui::ElementPosition::RELATIVE);
  relElem->setOffset(3.0F, 4.0F);
  ASSERT_TRUE(relElem->isOffsetDirty());
  relElem->updateOffset();
  ASSERT_FALSE(relElem->isOffsetDirty());
  absElem->addChildNode(relElem);
  ASSERT_EQ(relElem->getOffset(), math::point2f_t(1.0F, 2.0F));
}
