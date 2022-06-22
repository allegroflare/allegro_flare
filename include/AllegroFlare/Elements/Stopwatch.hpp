#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      class Stopwatch
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::string quote;

      public:
         Stopwatch(AllegroFlare::FontBin* font_bin=nullptr);
         ~Stopwatch();

         void render();
         ALLEGRO_FONT* obtain_font();
      };
   }
}



