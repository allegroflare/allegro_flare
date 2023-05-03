#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
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
         float width;
         float gutter_x;
         float gutter_padding;
         ALLEGRO_COLOR speaker_name_color;
         ALLEGRO_COLOR dialog_color;
         ALLEGRO_COLOR internal_dialog_color;
         ALLEGRO_FONT* obtain_font();
         ALLEGRO_FONT* obtain_internal_dialog_font();

      protected:


      public:
         DialogRollRenderer(AllegroFlare::FontBin* font_bin=nullptr, std::vector<std::pair<std::string, std::string>> roll={}, float width=1320);
         ~DialogRollRenderer();

         void set_width(float width);
         void set_gutter_x(float gutter_x);
         void set_gutter_padding(float gutter_padding);
         void set_speaker_name_color(ALLEGRO_COLOR speaker_name_color);
         void set_dialog_color(ALLEGRO_COLOR dialog_color);
         void set_internal_dialog_color(ALLEGRO_COLOR internal_dialog_color);
         float get_width() const;
         float get_gutter_x() const;
         float get_gutter_padding() const;
         ALLEGRO_COLOR get_speaker_name_color() const;
         ALLEGRO_COLOR get_dialog_color() const;
         ALLEGRO_COLOR get_internal_dialog_color() const;
         void render();
      };
   }
}



