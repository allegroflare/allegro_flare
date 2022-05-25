
#include <gtest/gtest.h>

#include <AllegroFlare/Timeline/ActorManager.hpp>


TEST(AllegroFlare_Timeline_ActorManagerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Timeline::ActorManager actor_manager;
}


TEST(AllegroFlare_Timeline_ActorManagerTest, run__returns_the_expected_response)
{
   AllegroFlare::Timeline::ActorManager actor_manager;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, actor_manager.run());
}

