#pragma once


#include <AllegroFlare/Story/Characters/PersonalityProfileMatrix.hpp>
#include <cstdint>
#include <string>


namespace AllegroFlare
{
   namespace Story
   {
      namespace Characters
      {
         class PersonalityProfileFactory
         {
         private:
            AllegroFlare::Story::Characters::PersonalityProfileMatrix personality_profile_matrix;
            bool initialized;

         protected:


         public:
            PersonalityProfileFactory();
            ~PersonalityProfileFactory();

            void initialize();
            std::string build_random_personality_profile(uint32_t num_traits=5, unsigned int seed=0);
            std::string ranking_level_to_text(uint32_t ranking_level=0);
         };
      }
   }
}



