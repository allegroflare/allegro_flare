#pragma once


#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace RollingCredits
      {
         namespace SectionRenderers
         {
            class Multicolumn : public AllegroFlare::Elements::RollingCredits::SectionRenderers::Base
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/Elements/RollingCredits/SectionRenderers/Multicolumn";

            private:
               AllegroFlare::FontBin* font_bin;
               std::vector<std::vector<std::string>> elements;
               float x;
               float y;
               float width;
               std::string element_alignment;
               std::string font_name;
               int font_size;
               ALLEGRO_COLOR text_color;
               float gutter_width;
               bool draw_debugging_guides;
               ALLEGRO_FONT* obtain_font();

            protected:


            public:
               Multicolumn(AllegroFlare::FontBin* font_bin=nullptr, std::vector<std::vector<std::string>> elements={}, float x=0.0f, float y=0.0f, float width=(1920.0f / 4 * 3), float gutter_width=40.0f);
               virtual ~Multicolumn();

               void set_font_bin(AllegroFlare::FontBin* font_bin);
               void set_elements(std::vector<std::vector<std::string>> elements);
               void set_x(float x);
               void set_y(float y);
               void set_width(float width);
               void set_font_name(std::string font_name);
               void set_font_size(int font_size);
               void set_text_color(ALLEGRO_COLOR text_color);
               void set_gutter_width(float gutter_width);
               void set_draw_debugging_guides(bool draw_debugging_guides);
               AllegroFlare::FontBin* get_font_bin() const;
               std::vector<std::vector<std::string>> get_elements() const;
               float get_x() const;
               float get_y() const;
               float get_width() const;
               std::string get_element_alignment() const;
               std::string get_font_name() const;
               int get_font_size() const;
               ALLEGRO_COLOR get_text_color() const;
               float get_gutter_width() const;
               bool get_draw_debugging_guides() const;
               void set_element_alignment(std::string element_alignment="[unset-element_alignment]");
               static bool valid_element_alignment(std::string element_alignment="[unset-element_alignment]");
               static int infer_al_text_alignment(std::string element_alignment="[unset-element_alignment]");
               static float infer_text_alignment_x_offset(std::string element_alignment="[unset-element_alignment]");
               virtual float render(bool only_calculate_height_dont_render=false) override;
            };
         }
      }
   }
}



