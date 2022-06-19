#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      class Base
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::string quote;

      public:
         Base(AllegroFlare::FontBin* font_bin=nullptr);
         ~Base();

         void render();
         ALLEGRO_FONT* obtain_font();
      };
   }
}



