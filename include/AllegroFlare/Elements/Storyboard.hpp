#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      class Storyboard : public AllegroFlare::Screens::Base
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::vector<std::string> pages;
         std::string font_name;
         int font_size;
         ALLEGRO_COLOR text_color;
         float top_padding;
         float left_padding;
         float right_padding;
         float line_height_multiplier;
         float line_height_padding;
         intptr_t current_page_num;
         int revealed_characters_count;
         bool can_advance_to_next;
         float can_advance_started_at;
         bool finished;

      public:
         Storyboard(AllegroFlare::FontBin* font_bin=nullptr, std::vector<std::string> pages={}, std::string font_name="Inter-Medium.ttf", int font_size=-60, ALLEGRO_COLOR text_color=ALLEGRO_COLOR{1, 1, 1, 1}, float top_padding=400, float left_padding=200, float right_padding=200, float line_height_multiplier=1.75f, float line_height_padding=0.0f, intptr_t current_page_num=0);
         ~Storyboard();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_pages(std::vector<std::string> pages);
         void set_font_name(std::string font_name);
         void set_font_size(int font_size);
         void set_text_color(ALLEGRO_COLOR text_color);
         void set_top_padding(float top_padding);
         void set_left_padding(float left_padding);
         void set_right_padding(float right_padding);
         void set_line_height_multiplier(float line_height_multiplier);
         void set_line_height_padding(float line_height_padding);
         std::string get_font_name();
         int get_font_size();
         ALLEGRO_COLOR get_text_color();
         float get_top_padding();
         float get_left_padding();
         float get_right_padding();
         float get_line_height_multiplier();
         float get_line_height_padding();
         intptr_t get_current_page_num();
         int get_revealed_characters_count();
         bool get_can_advance_to_next();
         float get_can_advance_started_at();
         bool get_finished();
         void update();
         void render();
         std::string current_page_text();
         std::string revealed_page_text();
         void reveal_all_characters();
         void render_next_button();
         void reset();
         bool permit_advancing_page();
         bool deny_advancing_page();
         bool advance();
         bool advance_page();
         bool all_characters_are_revealed();
         bool infer_at_last_page();
         bool infer_at_or_past_last_page();
         ALLEGRO_FONT* obtain_font();
         ALLEGRO_FONT* obtain_next_button_font();
      };
   }
}



