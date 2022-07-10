#pragma once


#include <AllegroFlare/Elements/StoryboardPages/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace StoryboardPages
      {
         class AdvancingText : public AllegroFlare::Elements::StoryboardPages::Base
         {
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

         public:
            AdvancingText(AllegroFlare::FontBin* font_bin=nullptr, std::string text="[text-not-set]", std::string font_name="Inter-Medium.ttf", int font_size=-60, ALLEGRO_COLOR text_color=ALLEGRO_COLOR{1, 1, 1, 1}, float top_padding=400, float left_padding=200, float right_padding=200, float line_height_multiplier=1.75f, float line_height_padding=0.0f);
            virtual ~AdvancingText();

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
            AllegroFlare::FontBin* get_font_bin();
            std::string get_text();
            std::string get_font_name();
            int get_font_size();
            ALLEGRO_COLOR get_text_color();
            float get_top_padding();
            float get_left_padding();
            float get_right_padding();
            float get_line_height_multiplier();
            float get_line_height_padding();
            int get_revealed_characters_count();
            virtual void start() override;
            virtual void update() override;
            virtual void render() override;
            virtual void advance() override;
            std::string generate_revealed_text();
            void reveal_all_characters();
            bool all_characters_are_revealed();
            ALLEGRO_FONT* obtain_font();
            ALLEGRO_FONT* obtain_next_button_font();
         };
      }
   }
}



