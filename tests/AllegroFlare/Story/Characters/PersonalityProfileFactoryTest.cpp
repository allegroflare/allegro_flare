
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
      personality_profile_factory.build_random_personality_profile("Yuki", 5, 86540);

   std::string expected_personality_profile_writeup = "In the personality category of \"Introversion vs. Extroversion\" (characters can vary in their preference for solitude or social interaction), Yuki ranks BALANCED, meaning Yuki can show signs of introversion or extraversion depending on the situation.\nIn the personality category of \"Openness to Experience\" (characters can differ in their curiosity, imagination, and willingness to embrace new ideas or experiences), Yuki ranks LOW, meaning Yuki generally avoids new experiences and ideas and is content with what is.\nIn the personality category of \"Agreeableness\" (this trait refers to how cooperative, empathetic, and friendly a character is), Yuki ranks BALANCED, meaning Yuki is neither agreeable or disagreeable.\nIn the personality category of \"Confidence vs. Insecurity\" (characters can vary in their self-assurance, self-belief, and level of confidence), Yuki ranks VERY_HIGH, meaning Yuki is overconfident and overly sure of themselves and their ideas.\nIn the personality category of \"Adventurousness\" (characters can vary in their desire for exploration, risk-taking, and seeking out new challenges.), Yuki ranks VERY_LOW, meaning Yuki avoids risks, exploring, and challenges.\n";
 
   EXPECT_EQ(expected_personality_profile_writeup, personality_profile_writeup);
}


