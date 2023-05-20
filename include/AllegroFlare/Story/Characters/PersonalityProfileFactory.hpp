#pragma once


#include <AllegroFlare/Story/Characters/PersonalityProfileMatrix.hpp>
#include <cstddef>
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
            std::string build_random_personality_profile(std::string character_name="this character", std::size_t num_traits=5, unsigned int seed=0);
            std::string build_writeup_for_dimension(std::string character_name="this character", std::string dimension_name="[unset-dimension_name]", std::string dimension_description="[unset-dimension_description]", uint32_t dimension_ranking_level=0, std::string dimension_descriptor_for_level="[unset-dimension_descriptor_for_level]");
            std::string ranking_level_to_text(uint32_t ranking_level=0);
         };
      }
   }
}



