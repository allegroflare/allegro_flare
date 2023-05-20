#pragma once


#include <AllegroFlare/Story/Characters/PersonalityProfile.hpp>


namespace AllegroFlare
{
   namespace Story
   {
      namespace Characters
      {
         class PersonalityProfileFactory
         {
         private:

         protected:


         public:
            PersonalityProfileFactory();
            ~PersonalityProfileFactory();

            AllegroFlare::Story::Characters::PersonalityProfile build_primary_personality_profile();
         };
      }
   }
}



