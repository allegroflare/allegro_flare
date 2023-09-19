#pragma once


#include <AllegroFlare/Elements/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      class Text : public AllegroFlare::Elements::Base
      {
      public:
         static constexpr char* DEFAULT_FONT_IDENTIFIER = (char*)"Inter-Regular.ttf";
         static constexpr int DEFAULT_FONT_SIZE = -48;

      private:
         AllegroFlare::FontBin* font_bin;
         std::string text;
         std::string font_identifier;
         int font_size;
         ALLEGRO_COLOR color;
         ALLEGRO_FONT* obtain_font();

      protected:


      public:
         Text(AllegroFlare::FontBin* font_bin=nullptr, std::string text="Hello Text", std::string font_identifier=DEFAULT_FONT_IDENTIFIER, int font_size=DEFAULT_FONT_SIZE, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
         ~Text();

         void set_text(std::string text);
         void set_font_identifier(std::string font_identifier);
         void set_font_size(int font_size);
         void set_color(ALLEGRO_COLOR color);
         std::string get_text() const;
         std::string get_font_identifier() const;
         int get_font_size() const;
         ALLEGRO_COLOR get_color() const;
         void render();
         void fit_placement_width_and_height_to_text();
      };
   }
}



