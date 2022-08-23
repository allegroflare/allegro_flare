#pragma once


#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace RollingCredits
      {
         namespace SectionRenderers
         {
            class Header : public AllegroFlare::Elements::RollingCredits::SectionRenderers::Base
            {
            private:
               AllegroFlare::FontBin* font_bin;
               std::string text;
               float x;
               float y;
               std::string font_name;
               int font_size;
               ALLEGRO_COLOR text_color;

            public:
               Header(AllegroFlare::FontBin* font_bin=nullptr, std::string text="[unset-text]");
               ~Header();

               void set_font_bin(AllegroFlare::FontBin* font_bin);
               void set_text(std::string text);
               void set_x(float x);
               void set_y(float y);
               void set_font_name(std::string font_name);
               void set_font_size(int font_size);
               void set_text_color(ALLEGRO_COLOR text_color);
               AllegroFlare::FontBin* get_font_bin();
               std::string get_text();
               float get_x();
               float get_y();
               std::string get_font_name();
               int get_font_size();
               ALLEGRO_COLOR get_text_color();
               float render();
               ALLEGRO_FONT* obtain_font();
            };
         }
      }
   }
}



