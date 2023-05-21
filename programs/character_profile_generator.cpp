#include <allegro5/allegro.h>
#include <AllegroFlare/Story/Characters/PersonalityProfileFactory.hpp>
#include <AllegroFlare/Generators/PersonNameGenerator.hpp>


int main(int argc, char **argv)
{
   int num_profiles_to_create = 10;
   int seed = 0;

   AllegroFlare::Story::Characters::PersonalityProfileFactory personality_profile_factory;
   personality_profile_factory.initialize();


   AllegroFlare::Story::Characters::PersonalityProfile result_profile =
      personality_profile_factory.build_random_personality_profile("Yuki", 5, 0);

   std::string actual_personality_profile_writeup = result_profile.build_personality_dimensions_writeup();

   EXPECT_EQ(expected_personality_profile_writeup, actual_personality_profile_writeup);


}


