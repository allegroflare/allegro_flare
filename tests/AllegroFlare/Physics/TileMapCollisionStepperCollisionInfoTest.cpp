
#include <gtest/gtest.h>

#include <AllegroFlare/Physics/TileMapCollisionStepperCollisionInfo.hpp>


TEST(AllegroFlare_Physics_TileMapCollisionStepperCollisionInfoTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo info;
}


TEST(AllegroFlare_Physics_TileMapCollisionStepperCollisionInfoTest,
   build_event_name__will_return_a_string_event_name_for_the_event)
{
   std::map<int, std::string> expected_types_and_names =
   {
      { AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_UNDEFINED,        "undefined" },
      { AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_ENTERED,          "entered" },
      { AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_EXITED,           "exited" },
      { AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_COLLIDED_AGAINST, "collided_against" },
   };

   for (auto &expected_type_and_name : expected_types_and_names)
   {
      std::string expected_name = expected_type_and_name.second;
      std::string actual_name = AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::build_event_name(
         expected_type_and_name.first
      );
      EXPECT_EQ(expected_name, actual_name);
   }
}


