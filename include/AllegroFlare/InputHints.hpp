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
      std::vector<std::pair<std::string, std::string>> input_hints_tokens;
      std::vector<std::string> keyboard_key_combo_tokens;
      int bar_height;
      ALLEGRO_COLOR text_color;
      int surface_width;
      int surface_height;

   public:
      InputHints(AllegroFlare::FontBin* font_bin=nullptr, std::vector<std::pair<std::string, std::string>> input_hints_tokens={}, std::vector<std::string> keyboard_key_combo_tokens={});
      ~InputHints();

      void set_font_bin(AllegroFlare::FontBin* font_bin);
      void set_input_hints_tokens(std::vector<std::pair<std::string, std::string>> input_hints_tokens);
      void set_keyboard_key_combo_tokens(std::vector<std::string> keyboard_key_combo_tokens);
      void set_bar_height(int bar_height);
      void set_text_color(ALLEGRO_COLOR text_color);
      void set_surface_width(int surface_width);
      void set_surface_height(int surface_height);
      AllegroFlare::FontBin* get_font_bin() const;
      std::vector<std::pair<std::string, std::string>> get_input_hints_tokens() const;
      std::vector<std::string> get_keyboard_key_combo_tokens() const;
      int get_bar_height() const;
      ALLEGRO_COLOR get_text_color() const;
      int get_surface_width() const;
      int get_surface_height() const;
      void render();
      void draw_inputs_bar();
      void draw_keyboard_key_combo_tokens();
      void draw_inputs_hints_tokens();
      static std::vector<std::pair<std::string, std::string>> build_placeholder_input_hints_tokens();
      ALLEGRO_FONT* obtain_font();
   };
}



