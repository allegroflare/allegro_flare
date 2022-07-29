#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>


namespace AllegroFlare
{
   namespace Elements
   {
      class DialogButton
      {
      private:
         AllegroFlare::FontBin* font_bin;
         int text_font_size;
         float started_at;
         bool at_last_advance;

      public:
         DialogButton(AllegroFlare::FontBin* font_bin=nullptr);
         ~DialogButton();

         void set_text_font_size(int text_font_size);
         void set_started_at(float started_at);
         void set_at_last_advance(bool at_last_advance);
         int get_text_font_size();
         float get_started_at();
         bool get_at_last_advance();
         void render();
         ALLEGRO_FONT* obtain_button_font();
      };
   }
}



