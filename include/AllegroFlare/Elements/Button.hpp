#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      class Button
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::string text;
         std::string text_font_name;
         int text_font_size;
         ALLEGRO_COLOR core_color;
         float started_at;
         float visibility_counter;
         float x;
         float y;
         float padding_x;
         float padding_y;
         ALLEGRO_FONT* obtain_button_font();

      protected:


      public:
         Button(AllegroFlare::FontBin* font_bin=nullptr);
         ~Button();

         void set_text(std::string text);
         void set_text_font_name(std::string text_font_name);
         void set_text_font_size(int text_font_size);
         void set_core_color(ALLEGRO_COLOR core_color);
         void set_started_at(float started_at);
         void set_visibility_counter(float visibility_counter);
         void set_x(float x);
         void set_y(float y);
         void set_padding_x(float padding_x);
         void set_padding_y(float padding_y);
         AllegroFlare::FontBin* get_font_bin() const;
         std::string get_text() const;
         std::string get_text_font_name() const;
         int get_text_font_size() const;
         ALLEGRO_COLOR get_core_color() const;
         float get_started_at() const;
         float get_visibility_counter() const;
         float get_x() const;
         float get_y() const;
         float get_padding_x() const;
         float get_padding_y() const;
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         float infer_box_width();
         float infer_box_height();
         void render();
         float infer_age();
      };
   }
}



