#include <sway/math.hpp>
#include <sway/ui.hpp>

#undef Bool
#undef None

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>
#include <utility>

namespace util {
template <std::size_t I>
using index_t = std::integral_constant<std::size_t, I>;

template <std::size_t SIZE, typename FUNC>
constexpr void foreacher(FUNC &&func) {
  auto unfold = [&]<std::size_t... ARGS>(
                    std::index_sequence<ARGS...>) { (std::forward<FUNC>(func)(index_t<ARGS>{}), ...); };

  unfold(std::make_index_sequence<SIZE>());
}
}  // namespace util

using namespace sway;

TEST(ElementTest, ctor_comps) {}

TEST(ElementTest, has_area) {
  ui::Element box;

  ASSERT_TRUE(box.getArea<ui::AreaType::IDX_MRG>().has_value());
  ASSERT_TRUE(box.getArea<ui::AreaType::IDX_BRD>().has_value());
  ASSERT_TRUE(box.getArea<ui::AreaType::IDX_PAD>().has_value());
  ASSERT_TRUE(box.getArea<ui::AreaType::IDX_CNT>().has_value());
}

TEST(ElementTest, get_area_index) {
  ui::Element box;

  ASSERT_EQ(box.getAreaIndex<ui::AreaType::IDX_MRG>(), 0);
  ASSERT_EQ(box.getAreaIndex<ui::AreaType::IDX_BRD>(), 1);
  ASSERT_EQ(box.getAreaIndex<ui::AreaType::IDX_PAD>(), 2);
  ASSERT_EQ(box.getAreaIndex<ui::AreaType::IDX_CNT>(), 3);
}

TEST(ElementTest, setter_getter) {
  ui::Element box;

  util::foreacher<NUM_OF_AREAS - 1 /* exclude AreaType::IDX_CNT */>([&](auto idx) {
    constexpr auto type = core::detail::toEnum<ui::AreaType>(idx + 0);

    box.setEdge<type, math::RectEdge::IDX_L>(1.0F);
    box.setEdge<type, math::RectEdge::IDX_T>(2.0F);
    box.setEdge<type, math::RectEdge::IDX_R>(3.0F);
    box.setEdge<type, math::RectEdge::IDX_B>(4.0F);

    auto area = box.getArea<type>();
    ASSERT_EQ(box.getEdge<math::RectEdge::IDX_L>(area), 1.0F);
    ASSERT_EQ(box.getEdge<math::RectEdge::IDX_T>(area), 2.0F);
    ASSERT_EQ(box.getEdge<math::RectEdge::IDX_R>(area), 3.0F);
    ASSERT_EQ(box.getEdge<math::RectEdge::IDX_B>(area), 4.0F);
  });
}

TEST(ElementTest, get_position) {
  ui::Element box;
  box.setEdge<ui::AreaType::IDX_MRG, math::RectEdge::IDX_L>(4.0F);
  box.setEdge<ui::AreaType::IDX_MRG, math::RectEdge::IDX_R>(4.0F);
  box.setEdge<ui::AreaType::IDX_MRG, math::RectEdge::IDX_T>(0.0F);
  box.setEdge<ui::AreaType::IDX_MRG, math::RectEdge::IDX_B>(0.0F);

  box.setEdge<ui::AreaType::IDX_BRD, math::RectEdge::IDX_L>(1.0F);
  box.setEdge<ui::AreaType::IDX_BRD, math::RectEdge::IDX_R>(1.0F);
  box.setEdge<ui::AreaType::IDX_BRD, math::RectEdge::IDX_T>(1.0F);
  box.setEdge<ui::AreaType::IDX_BRD, math::RectEdge::IDX_B>(1.0F);

  box.setEdge<ui::AreaType::IDX_PAD, math::RectEdge::IDX_L>(2.0F);
  box.setEdge<ui::AreaType::IDX_PAD, math::RectEdge::IDX_R>(2.0F);
  box.setEdge<ui::AreaType::IDX_PAD, math::RectEdge::IDX_T>(2.0F);
  box.setEdge<ui::AreaType::IDX_PAD, math::RectEdge::IDX_B>(2.0F);

  auto position = box.getPosition<ui::AreaType::IDX_CNT>();
  ASSERT_EQ(position.getX(), 7.0F);
  ASSERT_EQ(position.getY(), 3.0F);

  auto size = box.getSize<ui::AreaType::IDX_BRD>();
  ASSERT_EQ(size.getW(), 6.0F);
  ASSERT_EQ(size.getH(), 6.0F);
}
