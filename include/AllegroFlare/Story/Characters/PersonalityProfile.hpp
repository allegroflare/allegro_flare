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
            std::vector<AllegroFlare::Story::Characters::PersonalityDimension> dimensions;

         protected:


         public:
            PersonalityProfile(std::vector<AllegroFlare::Story::Characters::PersonalityDimension> dimensions={});
            ~PersonalityProfile();

            void set_dimensions(std::vector<AllegroFlare::Story::Characters::PersonalityDimension> dimensions);
            std::vector<AllegroFlare::Story::Characters::PersonalityDimension> get_dimensions() const;
         };
      }
   }
}



