#pragma once


#include <AllegroFlare/Story/Characters/PersonalityDimension.hpp>
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
            std::vector<AllegroFlare::Story::Characters::PersonalityDimension> personality_dimensions;

         protected:


         public:
            PersonalityProfile(std::vector<AllegroFlare::Story::Characters::PersonalityDimension> personality_dimensions={});
            ~PersonalityProfile();

            void set_personality_dimensions(std::vector<AllegroFlare::Story::Characters::PersonalityDimension> personality_dimensions);
            std::vector<AllegroFlare::Story::Characters::PersonalityDimension> get_personality_dimensions() const;
         };
      }
   }
}



