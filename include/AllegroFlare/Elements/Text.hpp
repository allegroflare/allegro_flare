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
      private:
         AllegroFlare::FontBin* font_bin;
         std::string text;
         ALLEGRO_COLOR color;
         ALLEGRO_FONT* obtain_font();

      protected:


      public:
         Text(AllegroFlare::FontBin* font_bin=nullptr, std::string text="Hello Text", ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
         ~Text();

         void set_text(std::string text);
         void set_color(ALLEGRO_COLOR color);
         std::string get_text() const;
         ALLEGRO_COLOR get_color() const;
         void render();
         void fit_placement_width_and_height_to_text();
      };
   }
}



