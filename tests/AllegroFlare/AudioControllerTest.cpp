
#include <gtest/gtest.h>

#include <AllegroFlare/AudioController.hpp>

TEST(AllegroFlare_AudioControllerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::AudioController audio_controller;
}

TEST(AllegroFlare_AudioControllerTest, run__returns_the_expected_response)
{
   AllegroFlare::AudioController audio_controller;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, audio_controller.run());
}
