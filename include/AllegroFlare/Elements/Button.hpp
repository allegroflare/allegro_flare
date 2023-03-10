#pragma once


#include <AllegroFlare/FontBin.hpp>
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
         float started_at;
         float x;
         float y;
         ALLEGRO_FONT* obtain_button_font();

      protected:


      public:
         Button(AllegroFlare::FontBin* font_bin=nullptr);
         ~Button();

         void set_text(std::string text);
         void set_text_font_name(std::string text_font_name);
         void set_text_font_size(int text_font_size);
         void set_started_at(float started_at);
         void set_x(float x);
         void set_y(float y);
         std::string get_text() const;
         std::string get_text_font_name() const;
         int get_text_font_size() const;
         float get_started_at() const;
         float get_x() const;
         float get_y() const;
         void render();
         float infer_age();
      };
   }
}



