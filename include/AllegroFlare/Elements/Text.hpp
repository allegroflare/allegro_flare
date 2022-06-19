#pragma once


#include <AllegroFlare/ElementID.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      class Text : public AllegroFlare::ElementID
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::string text;
         ALLEGRO_COLOR color;
         AllegroFlare::Placement2D placement;

      public:
         Text(AllegroFlare::FontBin* font_bin=nullptr, std::string text="Hello Text", ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, AllegroFlare::Placement2D placement={});
         ~Text();

         void set_text(std::string text);
         void set_color(ALLEGRO_COLOR color);
         void set_placement(AllegroFlare::Placement2D placement);
         std::string get_text();
         ALLEGRO_COLOR get_color();
         AllegroFlare::Placement2D get_placement();
         void render();
         void fit_placement_width_and_height_to_text();
         ALLEGRO_FONT* obtain_font();
      };
   }
}



