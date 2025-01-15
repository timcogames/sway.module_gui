#include <sway/ui.hpp>

#undef Bool
#undef None

#include <gtest/gtest.h>

#include <memory>

NS_SHORT_SWAY()

TEST(LayoutTest, ctor_def) {
  auto builder = std::make_shared<ui::Builder>(nullptr);
  builder->setEventBus(std::make_shared<core::EventBus>());
  builder->initialize();

  auto mainLayout = ui::LinearLayout::create(builder.get());
  EXPECT_EQ(mainLayout->getOrientation(), ui::Orientation::VERT);

  builder->getRootWidget()->removeChildNode(mainLayout);
  builder->deinit();
}

TEST(LayoutTest, build) {
  auto builder = std::make_shared<ui::Builder>(nullptr);
  builder->setEventBus(std::make_shared<core::EventBus>());
  builder->initialize();

  auto mainLayout = ui::LinearLayout::create(builder.get());
  mainLayout->setSize(800.0F, 600.0F);

  auto btn1 = ui::Button::create(builder.get(), "btn1");
  btn1->setAlignment(math::Alignment::LEFT_TOP);
  btn1->setOffset(0.0F, 0.0F);
  btn1->setSize(150.0F, 70.0F);
  mainLayout->addChildNode(btn1);

  auto btn2 = ui::Button::create(builder.get(), "btn2");
  btn2->setAlignment(math::Alignment::LEFT_TOP);
  btn2->setOffset(0.0F, 0.0F);
  btn2->setSize(150.0F, 70.0F);
  mainLayout->addChildNode(btn2);

  std::cout << "btn1: " << Representation<core::NodeIndex>::get(btn1->getNodeIndex())
            << " offset: " << btn1->getOffset().computed << std::endl;

  std::cout << "btn2: " << Representation<core::NodeIndex>::get(btn2->getNodeIndex())
            << " offset: " << btn2->getOffset().computed << std::endl;

  mainLayout->removeChildNode(btn2);
  mainLayout->removeChildNode(btn1);

  builder->getRootWidget()->removeChildNode(mainLayout);
  builder->deinit();
}

TEST(LayoutTest, build_center) {
  auto builder = std::make_shared<ui::Builder>(nullptr);
  builder->setEventBus(std::make_shared<core::EventBus>());
  builder->initialize();

  auto mainLayout = ui::LinearLayout::create(builder.get());
  mainLayout->setSize(800.0F, 600.0F);

  auto btn1 = ui::Button::create(builder.get(), "btn1");
  btn1->setAlignment(math::Alignment::CENTER);
  btn1->setOffset(0.0F, 0.0F);
  btn1->setSize(150.0F, 70.0F);
  mainLayout->addChildNode(btn1);

  auto btn2 = ui::Button::create(builder.get(), "btn2");
  btn2->setAlignment(math::Alignment::CENTER);
  btn2->setOffset(0.0F, 0.0F);
  btn2->setSize(150.0F, 70.0F);
  mainLayout->addChildNode(btn2);

  std::cout << "btn1: " << Representation<core::NodeIndex>::get(btn1->getNodeIndex())
            << " offset: " << btn1->getOffset().computed << std::endl;

  std::cout << "btn2: " << Representation<core::NodeIndex>::get(btn2->getNodeIndex())
            << " offset: " << btn2->getOffset().computed << std::endl;

  mainLayout->removeChildNode(btn2);
  mainLayout->removeChildNode(btn1);

  builder->getRootWidget()->removeChildNode(mainLayout);
  builder->deinit();
}
