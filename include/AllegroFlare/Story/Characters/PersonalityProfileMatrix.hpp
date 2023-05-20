#pragma once


#include <AllegroFlare/Story/Characters/PersonalityDimension.hpp>
#include <vector>


namespace AllegroFlare
{
   namespace Story
   {
      namespace Characters
      {
         class PersonalityProfileMatrix
         {
         private:
            std::vector<AllegroFlare::Story::Characters::PersonalityDimension> dimensions;

         protected:


         public:
            PersonalityProfileMatrix(std::vector<AllegroFlare::Story::Characters::PersonalityDimension> dimensions={});
            ~PersonalityProfileMatrix();

            void set_dimensions(std::vector<AllegroFlare::Story::Characters::PersonalityDimension> dimensions);
            std::vector<AllegroFlare::Story::Characters::PersonalityDimension> get_dimensions() const;
         };
      }
   }
}



