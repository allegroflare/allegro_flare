#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      class NotificationRenderer
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::string quote;

      public:
         NotificationRenderer(AllegroFlare::FontBin* font_bin=nullptr);
         ~NotificationRenderer();

         void render();
         void draw_box();
         ALLEGRO_FONT* obtain_font();
      };
   }
}



