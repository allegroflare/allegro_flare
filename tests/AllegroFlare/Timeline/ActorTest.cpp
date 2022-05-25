
#include <gtest/gtest.h>

#include <AllegroFlare/Timeline/Actor.hpp>


TEST(AllegroFlare_Timeline_ActorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Timeline::Actor actor;
}


TEST(AllegroFlare_Timeline_ActorTest, run__returns_the_expected_response)
{
   AllegroFlare::Timeline::Actor actor;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, actor.run());
}

