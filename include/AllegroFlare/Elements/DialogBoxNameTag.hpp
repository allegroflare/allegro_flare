#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      class DialogBoxNameTag
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::string name;
         float width;
         float height;
         void draw_text();
         ALLEGRO_FONT* obtain_dialog_font();

      protected:


      public:
         DialogBoxNameTag(AllegroFlare::FontBin* font_bin=nullptr, std::string name="[name-not-set]", float width=240, float height=70);
         ~DialogBoxNameTag();

         float get_width() const;
         float get_height() const;
         void render();
      };
   }
}



