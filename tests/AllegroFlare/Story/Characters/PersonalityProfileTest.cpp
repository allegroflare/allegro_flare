
#include <gtest/gtest.h>

#include <AllegroFlare/Story/Characters/PersonalityProfile.hpp>


TEST(AllegroFlare_Story_Characters_PersonalityProfileTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Story::Characters::PersonalityProfile personality_profile;
}


TEST(AllegroFlare_Story_Characters_PersonalityProfileTest, add_personality_dimension__will_add_the_dimension)
{
   AllegroFlare::Story::Characters::PersonalityProfile personality_profile;
   personality_profile.add_personality_dimension(
      AllegroFlare::Story::Characters::PersonalityProfileDimension(
         "Agreeableness",
         "this trait refers to how cooperative, empathetic, and friendly a character is",
         3,
         4,
         "is agreeable and cooperative"
      )
   );
}


