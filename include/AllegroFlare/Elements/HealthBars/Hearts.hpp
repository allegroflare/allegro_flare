#pragma once


#include <AllegroFlare/Elements/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <cstdint>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace HealthBars
      {
         class Hearts : public AllegroFlare::Elements::Base
         {
         private:
            AllegroFlare::FontBin* font_bin;
            int max;
            int value;
            ALLEGRO_COLOR fill_color;
            ALLEGRO_COLOR empty_color;
            ALLEGRO_COLOR outline_color;
            int heart_size;
            float heart_spacing;
            bool drawing_outline;
            std::string font_awesome_solid_font_name;
            std::string font_awesome_outline_font_name;
            ALLEGRO_FONT* obtain_font_awesome_solid_font();
            ALLEGRO_FONT* obtain_font_awesome_outline_font();

         protected:


         public:
            Hearts(AllegroFlare::FontBin* font_bin=nullptr, int max=10, int value=10, ALLEGRO_COLOR fill_color=(ALLEGRO_COLOR{0.86, 0.08, 0.24, 1} /*crimson*/), ALLEGRO_COLOR empty_color=(ALLEGRO_COLOR{0.25, 0.1, 0.25, 1}), ALLEGRO_COLOR outline_color=(ALLEGRO_COLOR{0.08, 0.12, 0.2, 1}), int heart_size=26, float heart_spacing=32, bool drawing_outline=true);
            ~Hearts();

            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_max(int max);
            void set_value(int value);
            void set_fill_color(ALLEGRO_COLOR fill_color);
            void set_empty_color(ALLEGRO_COLOR empty_color);
            void set_outline_color(ALLEGRO_COLOR outline_color);
            void set_heart_size(int heart_size);
            void set_heart_spacing(float heart_spacing);
            void set_drawing_outline(bool drawing_outline);
            int get_max() const;
            int get_value() const;
            ALLEGRO_COLOR get_fill_color() const;
            ALLEGRO_COLOR get_empty_color() const;
            ALLEGRO_COLOR get_outline_color() const;
            int get_heart_size() const;
            float get_heart_spacing() const;
            bool get_drawing_outline() const;
            void render() override;
            void draw_unicode_character(ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, int32_t icon=61444, int flags=0, float x=0.0f, float y=0.0f);
         };
      }
   }
}



