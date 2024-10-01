
#include <gtest/gtest.h>

#include <AllegroFlare/Tiled/TMJObject.hpp>
#include <AllegroFlare/Testing/Comparison/AllegroFlare/Vec2D.hpp>


TEST(AllegroFlare_Tiled_TMJObjectTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Tiled::TMJObject tmj_object;
}


TEST(AllegroFlare_Tiled_TMJObjectTest, center__will_return_the_center_of_the_objects_position_and_size)
{
   AllegroFlare::Tiled::TMJObject tmj_object;
   tmj_object.x = 100;
   tmj_object.y = 220;
   tmj_object.width = 70;
   tmj_object.height = 450;
   AllegroFlare::Vec2D expected_center = AllegroFlare::Vec2D(135, 445); 
   AllegroFlare::Vec2D actual_center = tmj_object.center();
   EXPECT_EQ(expected_center, actual_center);
}


