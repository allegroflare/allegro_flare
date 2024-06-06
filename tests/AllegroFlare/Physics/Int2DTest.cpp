
#include <gtest/gtest.h>

#include <AllegroFlare/Physics/Int2D.hpp>


TEST(AllegroFlare_Physics_Int2DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Physics::Int2D int2d;
}


TEST(AllegroFlare_Physics_Int2DTest, constructor_will_assign_the_values)
{
   AllegroFlare::Physics::Int2D int2d(3, 4);
   EXPECT_EQ(3, int2d.get_x());
   EXPECT_EQ(4, int2d.get_y());
}


TEST(AllegroFlare_Physics_Int2DTest, rotate__will_rotate_the_elements_in_the_class)
{
   AllegroFlare::Physics::Int2D int2d(3, 4);
   int2d.rotate();
   EXPECT_EQ(4, int2d.get_x());
   EXPECT_EQ(3, int2d.get_y());
}


