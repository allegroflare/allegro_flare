#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace HealthBars
      {
         class Classic
         {
         private:
            AllegroFlare::FontBin* font_bin;
            std::string quote;

         public:
            Classic(AllegroFlare::FontBin* font_bin=nullptr);
            ~Classic();

            void render();
            ALLEGRO_FONT* obtain_font();
         };
      }
   }
}



