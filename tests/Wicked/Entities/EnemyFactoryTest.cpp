
#include <gtest/gtest.h>

#include <Wicked/Entities/EnemyFactory.hpp>

TEST(Wicked_Entities_EnemyFactoryTest, can_be_created_without_blowing_up)
{
   Wicked::Entities::EnemyFactory enemy_factory;
}

TEST(Wicked_Entities_EnemyFactoryTest, run__returns_the_expected_response)
{
   Wicked::Entities::EnemyFactory enemy_factory;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, enemy_factory.run());
}
