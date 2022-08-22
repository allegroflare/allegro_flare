
#include <gtest/gtest.h>

#include <AllegroFlare/MotionComposer/Messages/TogglePlayback.hpp>


TEST(AllegroFlare_MotionComposer_Messages_TogglePlaybackTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MotionComposer::Messages::TogglePlayback toggle_playback;
}


TEST(AllegroFlare_MotionComposer_Messages_TogglePlaybackTest, has_the_expected_type)
{
   AllegroFlare::MotionComposer::Messages::TogglePlayback toggle_playback;
   EXPECT_EQ("TogglePlayback", toggle_playback.get_type());
}


