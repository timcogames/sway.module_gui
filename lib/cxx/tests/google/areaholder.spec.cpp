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

NS_SHORT_SWAY()

TEST(AreaHolderTest, ctor_comps) {}

TEST(AreaHolderTest, has_area) {
  ui::AreaHolder holder;

  ASSERT_TRUE(holder.getArea<ui::AreaType::IDX_MRG>().has_value());
  ASSERT_TRUE(holder.getArea<ui::AreaType::IDX_BRD>().has_value());
  ASSERT_TRUE(holder.getArea<ui::AreaType::IDX_PAD>().has_value());
  ASSERT_TRUE(holder.getArea<ui::AreaType::IDX_CNT>().has_value());
}

TEST(AreaHolderTest, get_area_index) {
  ui::AreaHolder holder;

  ASSERT_EQ(holder.getAreaIndex<ui::AreaType::IDX_MRG>(), 0);
  ASSERT_EQ(holder.getAreaIndex<ui::AreaType::IDX_BRD>(), 1);
  ASSERT_EQ(holder.getAreaIndex<ui::AreaType::IDX_PAD>(), 2);
  ASSERT_EQ(holder.getAreaIndex<ui::AreaType::IDX_CNT>(), 3);
}

TEST(AreaHolderTest, setter_getter) {
  ui::AreaHolder holder;

  util::foreacher<ui::NUM_AREA_TYPES_WITHOUT_CNT>([&](auto idx) {
    constexpr auto type = core::detail::toEnum<ui::AreaType>(idx + 0);

    holder.setEdge<type, math::RectEdge::Enum::IDX_L>(1.0F);
    holder.setEdge<type, math::RectEdge::Enum::IDX_T>(2.0F);
    holder.setEdge<type, math::RectEdge::Enum::IDX_R>(3.0F);
    holder.setEdge<type, math::RectEdge::Enum::IDX_B>(4.0F);

    auto area = holder.getArea<type>().value();
    ASSERT_EQ(holder.getEdge<math::RectEdge::Enum::IDX_L>(area), 1.0F);
    ASSERT_EQ(holder.getEdge<math::RectEdge::Enum::IDX_T>(area), 2.0F);
    ASSERT_EQ(holder.getEdge<math::RectEdge::Enum::IDX_R>(area), 3.0F);
    ASSERT_EQ(holder.getEdge<math::RectEdge::Enum::IDX_B>(area), 4.0F);
  });
}

TEST(AreaHolderTest, get_position) {
  ui::AreaHolder holder;
  holder.setEdge<ui::AreaType::IDX_MRG, math::RectEdge::Enum::IDX_L>(4.0F);
  holder.setEdge<ui::AreaType::IDX_MRG, math::RectEdge::Enum::IDX_R>(4.0F);
  holder.setEdge<ui::AreaType::IDX_MRG, math::RectEdge::Enum::IDX_T>(0.0F);
  holder.setEdge<ui::AreaType::IDX_MRG, math::RectEdge::Enum::IDX_B>(0.0F);

  holder.setEdge<ui::AreaType::IDX_BRD, math::RectEdge::Enum::IDX_L>(1.0F);
  holder.setEdge<ui::AreaType::IDX_BRD, math::RectEdge::Enum::IDX_R>(1.0F);
  holder.setEdge<ui::AreaType::IDX_BRD, math::RectEdge::Enum::IDX_T>(1.0F);
  holder.setEdge<ui::AreaType::IDX_BRD, math::RectEdge::Enum::IDX_B>(1.0F);

  holder.setEdge<ui::AreaType::IDX_PAD, math::RectEdge::Enum::IDX_L>(2.0F);
  holder.setEdge<ui::AreaType::IDX_PAD, math::RectEdge::Enum::IDX_R>(2.0F);
  holder.setEdge<ui::AreaType::IDX_PAD, math::RectEdge::Enum::IDX_T>(2.0F);
  holder.setEdge<ui::AreaType::IDX_PAD, math::RectEdge::Enum::IDX_B>(2.0F);

  auto position = holder.getPosition<ui::AreaType::IDX_CNT>();
  ASSERT_EQ(position.getX(), 7.0F);
  ASSERT_EQ(position.getY(), 3.0F);

  auto size = holder.getSize<ui::AreaType::IDX_BRD>();
  ASSERT_EQ(size.getW(), 6.0F);
  ASSERT_EQ(size.getH(), 6.0F);
}