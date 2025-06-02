#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
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
         ALLEGRO_COLOR fill_color;
         float fill_opacity;
         ALLEGRO_COLOR text_color;
         float opacity;
         void draw_text();
         ALLEGRO_FONT* obtain_dialog_font();

      protected:


      public:
         DialogBoxNameTag(AllegroFlare::FontBin* font_bin=nullptr, std::string name="[name-not-set]", float width=240, float height=70, ALLEGRO_COLOR fill_color=ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0}, float fill_opacity=1.0f, ALLEGRO_COLOR text_color=ALLEGRO_COLOR{0.0, 0.0, 0.0, 1.0}, float opacity=1.0f);
         ~DialogBoxNameTag();

         float get_width() const;
         float get_height() const;
         ALLEGRO_COLOR get_fill_color() const;
         float get_fill_opacity() const;
         ALLEGRO_COLOR get_text_color() const;
         float get_opacity() const;
         void render();
      };
   }
}



