#pragma once


#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>
#include <tuple>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace RollingCredits
      {
         namespace SectionRenderers
         {
            class ColumnWithLabels : public AllegroFlare::Elements::RollingCredits::SectionRenderers::Base
            {
            private:
               AllegroFlare::FontBin* font_bin;
               std::vector<std::tuple<std::string, std::string>> elements;
               float x;
               float y;
               std::string font_name;
               int font_size;
               ALLEGRO_COLOR text_color;
               float gutter_width;

            public:
               ColumnWithLabels(AllegroFlare::FontBin* font_bin=nullptr, std::vector<std::tuple<std::string, std::string>> elements={}, float x=0.0f, float y=0.0f, float gutter_width=40.0f);
               virtual ~ColumnWithLabels();

               void set_font_bin(AllegroFlare::FontBin* font_bin);
               void set_elements(std::vector<std::tuple<std::string, std::string>> elements);
               void set_x(float x);
               void set_y(float y);
               void set_font_name(std::string font_name);
               void set_font_size(int font_size);
               void set_text_color(ALLEGRO_COLOR text_color);
               void set_gutter_width(float gutter_width);
               AllegroFlare::FontBin* get_font_bin();
               std::vector<std::tuple<std::string, std::string>> get_elements();
               float get_x();
               float get_y();
               std::string get_font_name();
               int get_font_size();
               ALLEGRO_COLOR get_text_color();
               float get_gutter_width();
               virtual float calculate_height();
               float render();
               ALLEGRO_FONT* obtain_font();
            };
         }
      }
   }
}



