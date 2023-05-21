
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
   personality_profile_factory.build_random_personality_profile("Yuki", 5, 86545);

   std::string expected_personality_profile_writeup = "In the personality category of \"Openness to Experience\" "
      "(characters can differ in their curiosity, imagination, and willingness to embrace new ideas or experiences), "
      "Yuki ranks HIGH, meaning Yuki is exceptionally curious, imaginative, and open to new ideas.\nIn the "
      "personality category of \"Optimism vs. Pessimism\" (characters may have different outlooks on life, ranging "
      "from positive and hopeful to negative and cynical), Yuki ranks VERY_HIGH, meaning Yuki has a very optimistic "
      "personality.\nIn the personality category of \"Adventurousness\" (characters can vary in their desire for "
      "exploration, risk-taking, and seeking out new challenges.), Yuki ranks BALANCED, meaning Yuki is willing to "
      "take on an adventure if compelled to do so.\nIn the personality category of \"Empathy\" (the level of empathy "
      "a character possesses influences their ability to understand and connect with others' emotions), Yuki ranks "
      "VERY_HIGH, meaning Yuki has a high degree of empathy and easily understands others' emotions even when they "
      "may not.\nIn the personality category of \"Independence vs. Dependence\" (some characters may be self-reliant "
      "and autonomous, while others may rely more heavily on others for support), Yuki ranks VERY_HIGH, meaning Yuki "
      "is overly self-reliant and actively goes out of their way to not be dependent on others.\n";
 
   EXPECT_EQ(expected_personality_profile_writeup, personality_profile_writeup);
}


