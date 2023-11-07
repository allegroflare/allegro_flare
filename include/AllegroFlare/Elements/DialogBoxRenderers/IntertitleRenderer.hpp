#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace DialogBoxRenderers
      {
         class IntertitleRenderer
         {
         public:
            static constexpr char* DEFAULT_FONT_NAME = (char*)"Inter-Regular.ttf";
            static constexpr int DEFAULT_FONT_SIZE = -36;

         private:
            AllegroFlare::FontBin* font_bin;
            std::string text;
            std::string font_name;
            int font_size;
            ALLEGRO_COLOR text_color;
            float top_padding;
            float left_padding;
            float right_padding;
            float line_height_multiplier;
            float line_height_padding;
            int revealed_characters_count;
            float all_characters_revealed_at;
            float wait_duration_after_all_characters_are_revealed;
            ALLEGRO_FONT* obtain_font();
            ALLEGRO_FONT* obtain_next_button_font();

         protected:


         public:
            IntertitleRenderer(AllegroFlare::FontBin* font_bin=nullptr, std::string text="[text-not-set]", std::string font_name=DEFAULT_FONT_NAME, int font_size=DEFAULT_FONT_SIZE, ALLEGRO_COLOR text_color=ALLEGRO_COLOR{1, 1, 1, 1}, float top_padding=400, float left_padding=360, float right_padding=360, float line_height_multiplier=1.75f, float line_height_padding=0.0f);
            ~IntertitleRenderer();

            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_text(std::string text);
            void set_font_name(std::string font_name);
            void set_font_size(int font_size);
            void set_text_color(ALLEGRO_COLOR text_color);
            void set_top_padding(float top_padding);
            void set_left_padding(float left_padding);
            void set_right_padding(float right_padding);
            void set_line_height_multiplier(float line_height_multiplier);
            void set_line_height_padding(float line_height_padding);
            AllegroFlare::FontBin* get_font_bin() const;
            std::string get_text() const;
            std::string get_font_name() const;
            int get_font_size() const;
            ALLEGRO_COLOR get_text_color() const;
            float get_top_padding() const;
            float get_left_padding() const;
            float get_right_padding() const;
            float get_line_height_multiplier() const;
            float get_line_height_padding() const;
            int get_revealed_characters_count() const;
            float get_all_characters_revealed_at() const;
            float get_wait_duration_after_all_characters_are_revealed() const;
            void render();
            std::string generate_revealed_text();
            bool all_characters_are_revealed();
         };
      }
   }
}



