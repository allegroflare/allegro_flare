#include <allegro5/allegro.h>
#include <AllegroFlare/Story/Characters/PersonalityProfileFactory.hpp>
#include <AllegroFlare/Generators/PersonNameGenerator.hpp>
#include <sstream>
#include <iostream>


int main(int argc, char **argv)
{
   int num_profiles_to_create = 10;
   int seed = 0;

   std::stringstream output;

   AllegroFlare::Story::Characters::PersonalityProfileFactory personality_profile_factory;
   personality_profile_factory.initialize();

   AllegroFlare::Generators::PersonNameGenerator person_name_generator;
   person_name_generator.initialize();

   for (int i=0; i<num_profiles_to_create; i++)
   {
      std::string name = person_name_generator.generate_double_consecutive_t_name();
      AllegroFlare::Story::Characters::PersonalityProfile result_profile =
         personality_profile_factory.build_random_personality_profile(name, 5, 0);

      // Build the writeup
      std::string personality_profile_writeup = result_profile.build_personality_dimensions_writeup();

      // Output the results
      output << "```markdown" << std::endl;
      output << "# Character name: " << std::endl;
      output << name << std::endl;
      output << std::endl;
      output << "## Personality Profile: " << std::endl;
      output << personality_profile_writeup << std::endl;
      output << std::endl;
      output << "```" << std::endl;
   }

   std::cout << output.str() << std::endl;

   return 0;
}


