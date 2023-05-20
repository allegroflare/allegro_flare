#pragma once


#include <AllegroFlare/Story/Characters/PersonalityProfileMatrix.hpp>


namespace AllegroFlare
{
   namespace Story
   {
      namespace Characters
      {
         class PersonalityProfileMatrixFactory
         {
         private:

         protected:


         public:
            PersonalityProfileMatrixFactory();
            ~PersonalityProfileMatrixFactory();

            AllegroFlare::Story::Characters::PersonalityProfileMatrix build_standard_matrix();
         };
      }
   }
}



