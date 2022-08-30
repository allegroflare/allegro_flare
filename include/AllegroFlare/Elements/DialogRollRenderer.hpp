#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      class DialogRollRenderer
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::vector<std::pair<std::string, std::string>> roll;
         float gutter_x;
         float width;

      public:
         DialogRollRenderer(AllegroFlare::FontBin* font_bin=nullptr, std::vector<std::pair<std::string, std::string>> roll={});
         ~DialogRollRenderer();

         void render();
         ALLEGRO_FONT* obtain_font();
         ALLEGRO_FONT* obtain_italic_font();
      };
   }
}



