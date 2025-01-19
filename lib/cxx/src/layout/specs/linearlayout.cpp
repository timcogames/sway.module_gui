#include <sway/ui/area/specs/boxarea.hpp>
#include <sway/ui/builder.hpp>
#include <sway/ui/layout/specs/linearlayout.hpp>

namespace sway::ui {

auto LinearLayout::create(BuilderPtr_t builder, Orientation orien) -> LinearLayoutSharedPtr_t {
  return std::make_shared<LinearLayout>(builder, orien);
}

LinearLayout::LinearLayout(BuilderPtr_t builder, Orientation orien)
    : Layout(builder, orien) {}

auto LinearLayout::getTotalUsedSize() -> math::sizef_t {
  auto size = math::size2f_zero;

  foreachItems([&](LayoutItemSharedPtr_t item) {
    auto itemMargin = item->getAreaHolder().getArea<ui::AreaType::IDX_MRG>();
    if (!itemMargin.has_value()) {
      // Empty
    } else {
      BoxArea &margin = *itemMargin.value().get();
      size.set(size.getW() + margin.getLR(), size.getH() + margin.getTB());

      auto sizePolicy = item->getSizePolicy();
      if (sizePolicy.dimensions[math::Size<f32_t>::IDX_WDT].policy == SizePolicyType::FIXED ||
          sizePolicy.dimensions[math::Size<f32_t>::IDX_WDT].policy == SizePolicyType::WRAP_CONTENT) {
        if (item->getWeight() == 0.0F && getOrientation() == Orientation::HORZ) {
          size.setW(size.getW() + item->getAreaHolder().getContentSize().getW());
        }
      }

      if (sizePolicy.dimensions[math::Size<f32_t>::IDX_HGT].policy == SizePolicyType::FIXED ||
          sizePolicy.dimensions[math::Size<f32_t>::IDX_HGT].policy == SizePolicyType::WRAP_CONTENT) {
        if (item->getWeight() == 0.0F && getOrientation() == Orientation::VERT) {
          size.setH(size.getH() + item->getAreaHolder().getContentSize().getH());
        }
      }
    }
  });

  return size;
}

void LinearLayout::setAdjacentChildOffsets() {
  auto accum = math::point2f_zero;
  auto totalUsedSize = getTotalUsedSize();

  foreachItems([&](LayoutItemSharedPtr_t item) {
    item->setOffset(accum);

    if (getOrientation() == Orientation::HORZ) {
      if (item->getWeight() != 0.0F) {
        auto pwdt = Dimension();
        auto cwdt = getSizePolicy().dimensions[math::Size<f32_t>::IDX_WDT];

        auto parent = getParentNode();
        if (!parent.has_value()) {
          pwdt = cwdt;
          std::cout << "Parent is null " << std::get<0>(pwdt.value) << std::endl;
        } else {
          pwdt =
              core::NodeUtil::cast<LayoutItem>(parent.value())->getSizePolicy().dimensions[math::Size<f32_t>::IDX_WDT];
        }

        auto csize = (cwdt.policy == SizePolicyType::MATCH_PARENT) ? cwdt.value : pwdt.value;
        auto nsize = std::ceil(std::get<0>(csize) - totalUsedSize.getW()) * item->getWeight();
        std::cout << "horz: " << nsize << std::endl;
      }

      accum.setX(accum.getX() + Layout::calculatesAutoCellSize(this).getW());

    } else if (getOrientation() == Orientation::VERT) {
      if (item->getWeight() != 0.0F) {
        auto phgt = Dimension();
        auto chgt = getSizePolicy().dimensions[math::Size<f32_t>::IDX_HGT];

        auto parent = getParentNode();
        if (!parent.has_value()) {
          phgt = chgt;
        } else {
          phgt =
              core::NodeUtil::cast<LayoutItem>(parent.value())->getSizePolicy().dimensions[math::Size<f32_t>::IDX_HGT];
        }

        auto csize = (chgt.policy == SizePolicyType::MATCH_PARENT) ? chgt.value : phgt.value;
        auto nsize = std::ceil(std::get<0>(csize) - totalUsedSize.getH()) * item->getWeight();
        std::cout << "vert: " << nsize << std::endl;
      }

      accum.setY(accum.getY() + Layout::calculatesAutoCellSize(this).getH());
    }
  });
}

}  // namespace sway::ui
