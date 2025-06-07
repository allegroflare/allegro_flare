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
         ALLEGRO_COLOR background_color;
         float background_opacity;
         ALLEGRO_COLOR text_color;
         float opacity;
         void draw_text();
         ALLEGRO_FONT* obtain_dialog_font();

      protected:


      public:
         DialogBoxNameTag(AllegroFlare::FontBin* font_bin=nullptr, std::string name="[name-not-set]", float width=240, float height=70, ALLEGRO_COLOR background_color=ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0}, float background_opacity=1.0f, ALLEGRO_COLOR text_color=ALLEGRO_COLOR{0.0, 0.0, 0.0, 1.0}, float opacity=1.0f);
         ~DialogBoxNameTag();

         void set_background_color(ALLEGRO_COLOR background_color);
         void set_background_opacity(float background_opacity);
         void set_text_color(ALLEGRO_COLOR text_color);
         void set_opacity(float opacity);
         float get_width() const;
         float get_height() const;
         ALLEGRO_COLOR get_background_color() const;
         float get_background_opacity() const;
         ALLEGRO_COLOR get_text_color() const;
         float get_opacity() const;
         void render();
      };
   }
}



