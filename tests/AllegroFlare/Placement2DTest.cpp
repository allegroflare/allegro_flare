
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/CustomComparison.hpp>


#include <AllegroFlare/Placement2D.hpp>


TEST(AllegroFlare_Placement2DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Placement2D placement;
}


TEST(AllegroFlare_Placement2DTest, transform_coordinates__will_transform_a_list_of_vec2d_coordinates_into_the_placement)
{
   AllegroFlare::Placement2D placement;
   placement.position = {10, 27};
   std::vector<AllegroFlare::Vec2D> coordinates = { { 0, 0 }, { 10, 27 }, { 32, 64 } };

   placement.transform_coordinates(&coordinates);

   std::vector<AllegroFlare::Vec2D> expected_transformed_coordinates = { { -10, -27 }, { 0, 0 }, { 22, 37 } };

   EXPECT_EQ(expected_transformed_coordinates, coordinates);
}


