#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      class AdvancingTextRenderer
      {
      public:
         static constexpr float DEFAULT_REVEAL_RATE_CHARACTERS_PER_SECOND = 60.0f;
         static constexpr float MIN_REVEAL_RATE_CHARACTERS_PER_SECOND = 0.0001f;

      private:
         AllegroFlare::FontBin* font_bin;
         std::string text;
         std::string font_name;
         int font_size;
         ALLEGRO_COLOR text_color;
         float width;
         float line_height_multiplier;
         float line_height_padding;
         int revealed_characters_count;
         float reveal_started_at;
         float reveal_ended_at;
         float reveal_rate_characters_per_second;
         bool all_characters_are_revealed;
         std::string generate_revealed_text();
         ALLEGRO_FONT* obtain_font();

      protected:


      public:
         AdvancingTextRenderer(AllegroFlare::FontBin* font_bin=nullptr, std::string text="[text-not-set]", std::string font_name="Inter-Regular.ttf", int font_size=-60, ALLEGRO_COLOR text_color=ALLEGRO_COLOR{1, 1, 1, 1}, float width=900.0f, float line_height_multiplier=1.25f, float line_height_padding=0.0f);
         ~AdvancingTextRenderer();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_text(std::string text);
         void set_font_name(std::string font_name);
         void set_font_size(int font_size);
         void set_text_color(ALLEGRO_COLOR text_color);
         void set_width(float width);
         void set_line_height_multiplier(float line_height_multiplier);
         void set_line_height_padding(float line_height_padding);
         AllegroFlare::FontBin* get_font_bin() const;
         std::string get_text() const;
         std::string get_font_name() const;
         int get_font_size() const;
         ALLEGRO_COLOR get_text_color() const;
         float get_width() const;
         float get_line_height_multiplier() const;
         float get_line_height_padding() const;
         int get_revealed_characters_count() const;
         float get_reveal_started_at() const;
         float get_reveal_ended_at() const;
         float get_reveal_rate_characters_per_second() const;
         bool get_all_characters_are_revealed() const;
         void start();
         void set_reveal_rate_characters_per_second(float reveal_rate_characters_per_second=DEFAULT_REVEAL_RATE_CHARACTERS_PER_SECOND);
         void update();
         void render();
         void reveal_all_characters();
      };
   }
}



