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
         class Text : public AllegroFlare::Elements::StoryboardPages::Base
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
            ALLEGRO_FONT* obtain_font();

         protected:


         public:
            Text(AllegroFlare::FontBin* font_bin=nullptr, std::string text="[text-not-set]", std::string font_name="Inter-Medium.ttf", int font_size=-40, ALLEGRO_COLOR text_color=ALLEGRO_COLOR{1, 1, 1, 1}, float top_padding=400, float left_padding=200, float right_padding=200, float line_height_multiplier=1.75f, float line_height_padding=0.0f);
            virtual ~Text();

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
            virtual void start() override;
            virtual void update() override;
            virtual void render() override;
            virtual void advance() override;
         };
      }
   }
}



