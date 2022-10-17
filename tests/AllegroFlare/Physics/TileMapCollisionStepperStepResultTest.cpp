
#include <gtest/gtest.h>

#include <AllegroFlare/Physics/TileMapCollisionStepperStepResult.hpp>


static std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> build_setpper_step_result_fixture()
{
   using AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo;
   auto EVENT_ENTERED = AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_ENTERED;
   auto EVENT_STAYED_ON = AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_STAYED_ON;
   auto EVENT_EXITED = AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_EXITED;

   return std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo>({
      TileMapCollisionStepperCollisionInfo({3, 4}, 23, -8, 8, false, EVENT_STAYED_ON),
      TileMapCollisionStepperCollisionInfo({3, 5}, 28, -8, 8, false, EVENT_STAYED_ON),
      TileMapCollisionStepperCollisionInfo({2, 4}, 22, -8, 8, false, EVENT_ENTERED),
      TileMapCollisionStepperCollisionInfo({2, 5}, 27, -8, 8, false, EVENT_ENTERED),
      TileMapCollisionStepperCollisionInfo({2, 6}, -1, -8, 8, false, EVENT_ENTERED),
      TileMapCollisionStepperCollisionInfo({3, 6}, -1, -8, 8, false, EVENT_ENTERED),
      TileMapCollisionStepperCollisionInfo({3, 3}, 18, -8, 8, false, EVENT_EXITED),
      TileMapCollisionStepperCollisionInfo({4, 3}, 19, -8, 8, false, EVENT_EXITED),
      TileMapCollisionStepperCollisionInfo({4, 4}, 24, -8, 8, false, EVENT_EXITED),
      TileMapCollisionStepperCollisionInfo({4, 5}, 29, -8, 8, false, EVENT_EXITED),
   });
}



TEST(AllegroFlare_Physics_TileMapCollisionStepperStepResultTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Physics::TileMapCollisionStepperStepResult step_result;
}


TEST(AllegroFlare_Physics_TileMapCollisionStepperStepResultTest,
   subject_is_still_on_or_was_previously_on_tile_value__will_return_true_if_a_collision_matches_the_description)
{
   AllegroFlare::Physics::TileMapCollisionStepperStepResult step_result;
   step_result.set_collisions(build_setpper_step_result_fixture());

   // "is on" cases
   EXPECT_EQ(true, step_result.subject_is_still_on_or_was_previously_on_tile_value(23));
   EXPECT_EQ(true, step_result.subject_is_still_on_or_was_previously_on_tile_value(28));

   // "was previously on" cases
   EXPECT_EQ(true, step_result.subject_is_still_on_or_was_previously_on_tile_value(18));
   EXPECT_EQ(true, step_result.subject_is_still_on_or_was_previously_on_tile_value(19));
   EXPECT_EQ(true, step_result.subject_is_still_on_or_was_previously_on_tile_value(24));
   EXPECT_EQ(true, step_result.subject_is_still_on_or_was_previously_on_tile_value(29));
}


TEST(AllegroFlare_Physics_TileMapCollisionStepperStepResultTest,
   subject_is_still_on_or_was_previously_on_tile_value__will_return_false_if_no_collision_matches_the_description)
{
   AllegroFlare::Physics::TileMapCollisionStepperStepResult step_result;
   step_result.set_collisions(build_setpper_step_result_fixture());

   // "tiles just entered" cases
   EXPECT_EQ(false, step_result.subject_is_still_on_or_was_previously_on_tile_value(22));
   EXPECT_EQ(false, step_result.subject_is_still_on_or_was_previously_on_tile_value(27));
   EXPECT_EQ(false, step_result.subject_is_still_on_or_was_previously_on_tile_value(-1));

   // "tile completely not involved" case
   EXPECT_EQ(false, step_result.subject_is_still_on_or_was_previously_on_tile_value(7));
}


TEST(AllegroFlare_Physics_TileMapCollisionStepperStepResultTest,
   subject_entered_tile_value__will_return_true_if_the_subject_had_not_prevously_been_on_a_tile_value_and_now_is)
   // TODO
{
   //AllegroFlare::Physics::TileMapCollisionStepperStepResult step_result;
   //EXPECT_EQ(true, step_result.subject_entered_tile_value(22));
   //EXPECT_EQ(true, step_result.subject_entered_tile_value(27));
}


