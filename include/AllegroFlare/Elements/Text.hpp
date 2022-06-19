#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      class Text
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::string quote;

      public:
         Text(AllegroFlare::FontBin* font_bin=nullptr);
         ~Text();

         void render();
         ALLEGRO_FONT* obtain_font();
      };
   }
}



