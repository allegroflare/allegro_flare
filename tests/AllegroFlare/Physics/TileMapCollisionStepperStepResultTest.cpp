
#include <gtest/gtest.h>

#include <AllegroFlare/Physics/TileMapCollisionStepperStepResult.hpp>


TEST(AllegroFlare_Physics_TileMapCollisionStepperStepResultTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Physics::TileMapCollisionStepperStepResult step_result;
}


TEST(AllegroFlare_Physics_TileMapCollisionStepperStepResultTest,
   subject_is_on_or_was_previously_on_tile_value__will_return_true_if_the_collision_exists_matching_the_description)
   // TODO
{
   AllegroFlare::Physics::TileMapCollisionStepperStepResult step_result;
   step_result.set_collisions({
   });
}


TEST(AllegroFlare_Physics_TileMapCollisionStepperStepResultTest,
   subject_entered_tile_value__will_return_true_if_the_subject_had_not_prevously_been_on_a_tile_and_now_is)
   // TODO
{
   //AllegroFlare::Physics::TileMapCollisionStepperStepResult step_result;
}


