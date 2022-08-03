#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   class InputHints
   {
   private:
      AllegroFlare::FontBin* font_bin;
      std::vector<std::pair<std::string, std::string>> input_hints;
      ALLEGRO_COLOR text_color;
      int surface_width;
      int surface_height;
      int bar_height;

   public:
      InputHints(AllegroFlare::FontBin* font_bin=nullptr);
      ~InputHints();

      void set_text_color(ALLEGRO_COLOR text_color);
      void set_surface_width(int surface_width);
      void set_surface_height(int surface_height);
      void set_bar_height(int bar_height);
      ALLEGRO_COLOR get_text_color();
      int get_surface_width();
      int get_surface_height();
      int get_bar_height();
      void render();
      void draw_inputs_bar();
      void draw_inputs_text();
      static std::vector<std::pair<std::string, std::string>> build_placeholder_input_hints();
      ALLEGRO_FONT* obtain_font();
   };
}



