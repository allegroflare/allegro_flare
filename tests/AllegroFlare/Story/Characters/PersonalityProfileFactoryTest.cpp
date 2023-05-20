
#include <gtest/gtest.h>

#include <AllegroFlare/Story/Characters/PersonalityProfileFactory.hpp>


TEST(AllegroFlare_Story_Characters_PersonalityProfileFactoryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Story::Characters::PersonalityProfileFactory personality_profile_factory;
}


TEST(AllegroFlare_Story_Characters_PersonalityProfileFactoryTest, run__returns_the_expected_response)
{
   AllegroFlare::Story::Characters::PersonalityProfileFactory personality_profile_factory;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, personality_profile_factory.run());
}


