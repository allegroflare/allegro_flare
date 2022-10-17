
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
      { AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_STAYED_ON,        "stayed_on" },
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


TEST(AllegroFlare_Physics_TileMapCollisionStepperCollisionInfoTest,
   is_tile_value__will_return_true_if_the_tile_value_matches)
{
   AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo info;
   info.set_tile_value(123);
   EXPECT_EQ(true, info.is_tile_value(123));
}


TEST(AllegroFlare_Physics_TileMapCollisionStepperCollisionInfoTest,
   is_tile_value__will_return_false_if_the_tile_value_matches)
{
   AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo info;
   info.set_tile_value(123);
   EXPECT_EQ(false, info.is_tile_value(999));
}


TEST(AllegroFlare_Physics_TileMapCollisionStepperCollisionInfoTest,
   is_event__will_return_true_if_the_tile_value_matches)
{
   AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo info;
   info.set_event(AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_ENTERED);
   EXPECT_EQ(true, info.is_event(AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_ENTERED));
}


TEST(AllegroFlare_Physics_TileMapCollisionStepperCollisionInfoTest,
   is_event__will_return_false_if_the_tile_value_matches)
{
   AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo info;
   info.set_event(AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_ENTERED);
   EXPECT_EQ(false, info.is_event(AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_EXITED));
}


