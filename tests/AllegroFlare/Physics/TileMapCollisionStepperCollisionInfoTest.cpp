
#include <gtest/gtest.h>

#include <AllegroFlare/Physics/TileMapCollisionStepperCollisionInfo.hpp>


TEST(AllegroFlare_Physics_TileMapCollisionStepperCollisionInfoTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo tile_map_collision_stepper_collision_info;
}


TEST(AllegroFlare_Physics_TileMapCollisionStepperCollisionInfoTest, run__returns_the_expected_response)
{
   AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo tile_map_collision_stepper_collision_info;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, tile_map_collision_stepper_collision_info.run());
}


