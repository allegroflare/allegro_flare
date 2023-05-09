#pragma once


#include <AllegroFlare/Elements/StoryboardPages/Base.hpp>
#include <ClubCatt/Logo.hpp>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace StoryboardPages
      {
         class ClubCattLogo : public AllegroFlare::Elements::StoryboardPages::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/Elements/StoryboardPages/ClubCattLogo";

         private:
            ClubCatt::Logo clubcatt_logo;

         protected:


         public:
            ClubCattLogo();
            ~ClubCattLogo();

            void initialize();
            void primary_timer_func();
         };
      }
   }
}



