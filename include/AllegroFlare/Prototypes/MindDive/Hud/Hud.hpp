#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace MindDive
      {
         namespace Hud
         {
            class Hud
            {
            private:
               AllegroFlare::FontBin* font_bin;
               std::string slate_text;
               void render_slate();
               ALLEGRO_FONT* obtain_font();

            protected:


            public:
               Hud(AllegroFlare::FontBin* font_bin=nullptr, std::string slate_text="-- WIN --");
               ~Hud();

               void render();
            };
         }
      }
   }
}



