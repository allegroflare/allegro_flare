#pragma once


#include <AllegroFlare/Story/Characters/PersonalityProfileDimension.hpp>
#include <cstddef>
#include <vector>


namespace AllegroFlare
{
   namespace Story
   {
      namespace Characters
      {
         class PersonalityProfile
         {
         private:
            std::vector<AllegroFlare::Story::Characters::PersonalityProfileDimension> personality_dimensions;

         protected:


         public:
            PersonalityProfile(std::vector<AllegroFlare::Story::Characters::PersonalityProfileDimension> personality_dimensions={});
            ~PersonalityProfile();

            void set_personality_dimensions(std::vector<AllegroFlare::Story::Characters::PersonalityProfileDimension> personality_dimensions);
            std::vector<AllegroFlare::Story::Characters::PersonalityProfileDimension> get_personality_dimensions() const;
            AllegroFlare::Story::Characters::PersonalityProfileDimension get_personality_dimension_by_index(std::size_t index=0);
         };
      }
   }
}



