
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/Comparison/AllegroFlare/Physics/TileMapCollisionStepperCollisionInfo.hpp>


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_Physics_TileMapCollisionStepperCollisionInfoTest,
   PrintTo__with_an_AllegroFlare_TileMapCollisionStepperCollisionInfo__will_output_as_expected)
{
   std::stringstream ss;
   AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo vec(
      AllegroFlare::Physics::Int2D(3, 4),
      123,
      0.9f,
      -0.2f,
      false,
      AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_ENTERED,
      AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::CollidingBlockEdge::EDGE_RIGHT
   );

   PrintTo(vec, &ss);

   std::string expected_output = "TileMapCollisionStepperCollisionInfo({3, 4}, 123, 0.9, -0.2, false, right_edge)";
   std::string actual_output = ss.str();
   EXPECT_EQ(expected_output, actual_output);
}


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_Physics_TileMapCollisionStepperCollisionInfoTest,
   equality_operator__works_with_google_test_EXPECT_statement)
{
   AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo vec;
   AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo other_vec;

   EXPECT_EQ(vec, other_vec);
}


