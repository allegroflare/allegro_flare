
#include <gtest/gtest.h>

#include <AllegroFlare/Story/Characters/PersonalityProfileFactory.hpp>


TEST(AllegroFlare_Story_Characters_PersonalityProfileFactoryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Story::Characters::PersonalityProfileFactory personality_profile_factory;
}


TEST(AllegroFlare_Story_Characters_PersonalityProfileFactoryTest, initialized__can_be_called_without_blowing_up)
{
   AllegroFlare::Story::Characters::PersonalityProfileFactory personality_profile_factory;
   personality_profile_factory.initialize();
}


TEST(AllegroFlare_Story_Characters_PersonalityProfileFactoryTest,
   build_random_personality_profile__will_write_a_personality_profile)
{
   AllegroFlare::Story::Characters::PersonalityProfileFactory personality_profile_factory;
   personality_profile_factory.initialize();
   std::string personality_profile_writeup =
      personality_profile_factory.build_random_personality_profile("Yuki", 3, 54321);

   std::string expected_personality_profile_writeup = "foo";
 
   EXPECT_EQ(expected_personality_profile_writeup, personality_profile_writeup);
}


