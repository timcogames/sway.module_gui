#include <sway/math.hpp>
#include <sway/ui.hpp>

#undef Bool
#undef None

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>
#include <utility>

using namespace sway;

template <std::size_t SIZE, typename FUNCTION>
constexpr void constexpr_for(FUNCTION &&func) {
  auto unfold = [&]<std::size_t... ARGS>(std::index_sequence<ARGS...>) {
    (std::forward<FUNCTION>(func)(std::integral_constant<std::size_t, ARGS>{}), ...);
  };

  unfold(std::make_index_sequence<SIZE>());
}

TEST(ElementBoxTest, ctor_comps) {}

TEST(ElementBoxTest, has_area) {
  ui::widget::ElementBox box;

  ASSERT_TRUE(box.getArea<math::AreaType::MRG>().has_value());
  ASSERT_TRUE(box.getArea<math::AreaType::BRD>().has_value());
  ASSERT_TRUE(box.getArea<math::AreaType::PAD>().has_value());
  ASSERT_TRUE(box.getArea<math::AreaType::CNT>().has_value());
}

TEST(ElementBoxTest, get_area_index) {
  ui::widget::ElementBox box;

  ASSERT_EQ(box.getAreaIndex<math::AreaType::MRG>(), 0);
  ASSERT_EQ(box.getAreaIndex<math::AreaType::BRD>(), 1);
  ASSERT_EQ(box.getAreaIndex<math::AreaType::PAD>(), 2);
  ASSERT_EQ(box.getAreaIndex<math::AreaType::CNT>(), 3);
}

TEST(ElementBoxTest, setter_getter_margin) {
  ui::widget::ElementBox box;

  constexpr_for<NUM_OF_AREAS - 1 /* exclude AreaType::CNT */>([&](auto i) {
    constexpr auto type = core::detail::toEnum<math::AreaType>(i + 1);

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

TEST(ElementBoxTest, get_position) {
  ui::widget::ElementBox box;
  box.setEdge<math::AreaType::MRG, math::RectEdge::IDX_L>(4.0F);
  box.setEdge<math::AreaType::MRG, math::RectEdge::IDX_R>(4.0F);
  box.setEdge<math::AreaType::MRG, math::RectEdge::IDX_T>(0.0F);
  box.setEdge<math::AreaType::MRG, math::RectEdge::IDX_B>(0.0F);

  box.setEdge<math::AreaType::BRD, math::RectEdge::IDX_L>(1.0F);
  box.setEdge<math::AreaType::BRD, math::RectEdge::IDX_R>(1.0F);
  box.setEdge<math::AreaType::BRD, math::RectEdge::IDX_T>(1.0F);
  box.setEdge<math::AreaType::BRD, math::RectEdge::IDX_B>(1.0F);

  box.setEdge<math::AreaType::PAD, math::RectEdge::IDX_L>(2.0F);
  box.setEdge<math::AreaType::PAD, math::RectEdge::IDX_R>(2.0F);
  box.setEdge<math::AreaType::PAD, math::RectEdge::IDX_T>(2.0F);
  box.setEdge<math::AreaType::PAD, math::RectEdge::IDX_B>(2.0F);

  auto position = box.getPosition<math::AreaType::CNT>();
  ASSERT_EQ(position.getX(), 7.0F);
  ASSERT_EQ(position.getY(), 3.0F);
}
