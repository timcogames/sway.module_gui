#include <sway/ui.hpp>

#undef Bool
#undef None

#include <gtest/gtest.h>

#include <memory>

NS_SHORT_SWAY()

TEST(LayoutTest, ctor_def) {
  auto eventBus = std::make_shared<core::evts::EventBus>();
  auto builder = std::make_shared<ui::Builder>(nullptr);

  builder->setEventBus(eventBus);
  builder->initialize();

  auto mainLayout = std::make_shared<ui::widget::LinearLayout>(builder.get(), ui::Orientation::HORZ);
  EXPECT_NE(mainLayout, nullptr);

  auto btn1 = std::make_shared<ui::widget::Button>(builder.get(), "btn1");
  btn1->setAlignment(math::Alignment::CENTER);
  btn1->setOffset(0.0F, 0.0F);
  btn1->setSize(150.0F, 70.0F);
  mainLayout->addChildNode(btn1);

  auto btn2 = std::make_shared<ui::widget::Button>(builder.get(), "btn2");
  btn2->setAlignment(math::Alignment::CENTER);
  btn2->setOffset(0.0F, 0.0F);
  btn2->setSize(150.0F, 70.0F);
  mainLayout->addChildNode(btn2);

  mainLayout->build();

  std::cout << btn1->getOffset().computed << std::endl;
  std::cout << btn2->getOffset().computed << std::endl;

  mainLayout->removeChildNode(btn2);
  mainLayout->removeChildNode(btn1);
  builder->getRootWidget()->removeChildNode(mainLayout);

  builder->deinit();
}
