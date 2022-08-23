
#include <gtest/gtest.h>

#include <AllegroFlare/MotionComposer/Messages/Clear.hpp>


TEST(AllegroFlare_MotionComposer_Messages_ClearTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MotionComposer::Messages::Clear clear;
}


TEST(AllegroFlare_MotionComposer_Messages_ClearTest, has_the_expected_type)
{
   AllegroFlare::MotionComposer::Messages::Clear clear;
   EXPECT_EQ("Clear", clear.get_type());
}


