#include <sway/math.hpp>
#include <sway/ui.hpp>
#include <sway/ui/element/event/specs/mouseevent.hpp>

#undef Bool
#undef None

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>
#include <utility>

NS_SHORT_SWAY()

class ElementImpl : public ui::Element {
public:
  virtual void recursiveUpdateItemOffset(const math::point2f_t parentOffset) {
    // TODO
  }
};

TEST(ElementTest, ctor_def) {
  ElementImpl elem;

  ASSERT_EQ(elem.getPosition(), ui::ElementPosition::RELATIVE);
  ASSERT_EQ(elem.getOffset().computed, math::point2f_zero);
  ASSERT_FALSE(elem.getOffset().dirty);
}

TEST(ElementTest, position) {
  ElementImpl elem;

  elem.setPosition(ui::ElementPosition::ABSOLUTE);
  ASSERT_EQ(elem.getPosition(), ui::ElementPosition::ABSOLUTE);
}
