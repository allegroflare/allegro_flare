#pragma once


#include <AllegroFlare/Story/Characters/PersonalityProfile.hpp>
#include <AllegroFlare/Story/Characters/PersonalityProfileMatrix.hpp>


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
            AllegroFlare::Story::Characters::PersonalityProfile build_random_personality_profile();
         };
      }
   }
}



