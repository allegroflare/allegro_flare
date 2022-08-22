
#include <gtest/gtest.h>

#include <AllegroFlare/MotionComposer/Messages/TogglePlaying.hpp>


TEST(AllegroFlare_MotionComposer_Messages_TogglePlayingTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MotionComposer::Messages::TogglePlaying toggle_playing;
}


TEST(AllegroFlare_MotionComposer_Messages_TogglePlayingTest, has_the_expected_type)
{
   AllegroFlare::MotionComposer::Messages::TogglePlaying toggle_playing;
   EXPECT_EQ("TogglePlaying", toggle_playing.get_type());
}


