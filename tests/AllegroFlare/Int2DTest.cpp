
#include <gtest/gtest.h>

#include <AllegroFlare/Int2D.hpp>


TEST(AllegroFlare_Int2DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Int2D int2d;
}


TEST(AllegroFlare_Int2DTest, constructor_will_assign_the_values)
{
   AllegroFlare::Int2D int2d(3, 4);
   EXPECT_EQ(3, int2d.x);
   EXPECT_EQ(4, int2d.y);
}


TEST(AllegroFlare_Int2DTest, rotate__will_rotate_the_elements_in_the_class)
{
   AllegroFlare::Int2D int2d(3, 4);
   int2d.rotate();
   EXPECT_EQ(4, int2d.x);
   EXPECT_EQ(3, int2d.y);
}


