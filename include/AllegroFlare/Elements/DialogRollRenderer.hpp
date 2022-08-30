#pragma once


#include <AllegroFlare/Elements/DialogRoll.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>


namespace AllegroFlare
{
   namespace Elements
   {
      class DialogRollRenderer
      {
      private:
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::Elements::DialogRoll* dialog_roll;

      public:
         DialogRollRenderer(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::Elements::DialogRoll* dialog_roll=nullptr);
         ~DialogRollRenderer();

         void render();
         ALLEGRO_FONT* obtain_font();
         ALLEGRO_FONT* obtain_italic_font();
      };
   }
}



