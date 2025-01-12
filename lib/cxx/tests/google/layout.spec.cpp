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
  mainLayout->setSize(800, 600);

  auto btn1 = ui::Button::create(builder.get(), "btn1");
  btn1->setAlignment(math::Alignment::CENTER);
  btn1->setOffset(10.0F, 20.0F);
  btn1->setSize(100.0F, 30.0F);
  mainLayout->addChildNode(btn1);

  // btn1->update();

  auto btn2 = ui::Button::create(builder.get(), "btn2");
  btn2->setAlignment(math::Alignment::CENTER);
  btn2->setOffset(50.0F, 100.0F);
  btn2->setSize(150.0F, 70.0F);
  mainLayout->addChildNode(btn2);

  // btn2->update();

  // mainLayout->build();

  auto txt1 = core::NodeUtil::cast<ui::TextView>(btn1->getChildNodes()[0]);
  std::cout << "btn1: " << core::Representation<core::NodeIndex>::get(btn1->getNodeIndex())
            << " offset: " << btn1->getOffset().computed << std::endl;
  std::cout << "txt1: " << core::Representation<core::NodeIndex>::get(txt1->getNodeIndex())
            << " offset: " << txt1->getOffset().computed << std::endl;

  auto txt2 = core::NodeUtil::cast<ui::TextView>(btn2->getChildNodes()[0]);
  std::cout << "btn2: " << core::Representation<core::NodeIndex>::get(btn2->getNodeIndex())
            << " offset: " << btn2->getOffset().computed << std::endl;
  std::cout << "txt2: " << core::Representation<core::NodeIndex>::get(txt2->getNodeIndex())
            << " offset: " << txt2->getOffset().computed << std::endl;

  mainLayout->removeChildNode(btn2);
  mainLayout->removeChildNode(btn1);

  builder->getRootWidget()->removeChildNode(mainLayout);
  builder->deinit();
}
