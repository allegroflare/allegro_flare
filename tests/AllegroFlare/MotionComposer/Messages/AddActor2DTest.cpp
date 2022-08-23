
#include <gtest/gtest.h>

#include <AllegroFlare/MotionComposer/Messages/AddActor2D.hpp>


TEST(AllegroFlare_MotionComposer_Messages_AddActor2DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MotionComposer::Messages::AddActor2D add_actor2d;
}


TEST(AllegroFlare_MotionComposer_Messages_AddActor2DTest, has_the_expected_type)
{
   AllegroFlare::MotionComposer::Messages::AddActor2D add_actor2d;
   EXPECT_EQ("AddActor2D", add_actor2d.get_type());
}


