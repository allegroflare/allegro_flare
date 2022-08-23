#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Screens
   {
      class RollingCredits : public AllegroFlare::Screens::Base
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::string property;

      public:
         RollingCredits(AllegroFlare::FontBin* font_bin=nullptr, std::string property="[unset-property]");
         ~RollingCredits();

         std::string get_property();
         void render();
         ALLEGRO_FONT* obtain_font();
      };
   }
}



