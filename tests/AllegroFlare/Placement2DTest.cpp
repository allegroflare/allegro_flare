
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/CustomComparison.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Placement2DTest : public ::testing::Test
{};

class AllegroFlare_Placement2DWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



#include <AllegroFlare/Placement2D.hpp>


TEST_F(AllegroFlare_Placement2DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Placement2D placement;
}


TEST_F(AllegroFlare_Placement2DTest,
   transform_coordinates__will_transform_a_list_of_vec2d_coordinates_into_the_placement)
{
   AllegroFlare::Placement2D placement;
   placement.position = {10, 27};
   std::vector<AllegroFlare::Vec2D> coordinates = { { 0, 0 }, { 10, 27 }, { 32, 64 } };

   placement.transform_coordinates(&coordinates);

   std::vector<AllegroFlare::Vec2D> expected_transformed_coordinates = { { -10, -27 }, { 0, 0 }, { 22, 37 } };

   EXPECT_EQ(expected_transformed_coordinates, coordinates);
}


TEST_F(AllegroFlare_Placement2DWithAllegroRenderingFixtureTest,
   collides__will_return_true_if_the_placement_collides_with_another_placement)
{
   // TODO
}


