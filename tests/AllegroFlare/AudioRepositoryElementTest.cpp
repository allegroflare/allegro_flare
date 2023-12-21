
#include <gtest/gtest.h>

#include <AllegroFlare/AudioRepositoryElement.hpp>


TEST(AllegroFlare_AudioRepositoryElementTest, can_be_created_without_blowing_up)
{
   AllegroFlare::AudioRepositoryElement audio_repository_element;
}


TEST(AllegroFlare_AudioRepositoryElementTest, filename__has_the_expected_default_value)
{
   AllegroFlare::AudioRepositoryElement audio_repository_element;
   std::string expected_default = "a-default-audio-repository-filename.ogg";
   EXPECT_EQ(expected_default, audio_repository_element.get_filename());
}


TEST(AllegroFlare_AudioRepositoryElementTest, loop__has_the_expected_default_value)
{
   AllegroFlare::AudioRepositoryElement audio_repository_element;
   bool expected_default = false;
   EXPECT_EQ(expected_default, audio_repository_element.get_loop());
}


TEST(AllegroFlare_AudioRepositoryElementTest, OVERPLAY_STRATEGY_IGNORE__contains_the_expected_value)
{
   EXPECT_EQ("ignore", AllegroFlare::AudioRepositoryElement::OVERPLAY_STRATEGY_IGNORE);
}


TEST(AllegroFlare_AudioRepositoryElementTest, OVERPLAY_STRATEGY_RESTART__contains_the_expected_value)
{
   EXPECT_EQ("restart", AllegroFlare::AudioRepositoryElement::OVERPLAY_STRATEGY_RESTART);
}


TEST(AllegroFlare_AudioRepositoryElementTest, overplay_strategy__is_set_to_OVERPLAY_STRATEGY_IGNORE_by_default)
{
   AllegroFlare::AudioRepositoryElement audio_repository_element;
   EXPECT_EQ(
      AllegroFlare::AudioRepositoryElement::OVERPLAY_STRATEGY_IGNORE,
      audio_repository_element.get_overplay_strategy()
   );
}


