

#include <AllegroFlare/Useful.hpp>


#include <gtest/gtest.h>



// There are currently no tests for this class

TEST(AllegroFlare_UsefulTest, distance__will_return_the_distance_between_two_3d_points)
{
   AllegroFlare::Vec3D point_a(1, 3, -2);
   AllegroFlare::Vec3D point_b(2, 4, -1);

   float expected_distance = 1.73205080757;
   float actual_distance = AllegroFlare::distance(point_a, point_b);

   EXPECT_EQ(expected_distance, actual_distance);
}



