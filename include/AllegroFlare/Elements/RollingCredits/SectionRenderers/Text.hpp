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
            class Text : public AllegroFlare::Elements::RollingCredits::SectionRenderers::Base
            {
            public:
               static constexpr char* TYPE = (char*)"SectionRenderers/Text";

            private:
               AllegroFlare::FontBin* font_bin;
               std::string text;
               std::string alignment;
               float x;
               float y;
               float max_width;
               std::string font_name;
               int font_size;
               ALLEGRO_COLOR text_color;
               static int _multiline_text_line_number;
               ALLEGRO_FONT* obtain_font();

            protected:


            public:
               Text(AllegroFlare::FontBin* font_bin=nullptr, std::string text="[unset-text]", std::string alignment="[unset-alignment]");
               virtual ~Text();

               void set_font_bin(AllegroFlare::FontBin* font_bin);
               void set_text(std::string text);
               void set_alignment(std::string alignment);
               void set_x(float x);
               void set_y(float y);
               void set_max_width(float max_width);
               void set_font_name(std::string font_name);
               void set_font_size(int font_size);
               void set_text_color(ALLEGRO_COLOR text_color);
               AllegroFlare::FontBin* get_font_bin() const;
               std::string get_text() const;
               std::string get_alignment() const;
               float get_x() const;
               float get_y() const;
               float get_max_width() const;
               std::string get_font_name() const;
               int get_font_size() const;
               ALLEGRO_COLOR get_text_color() const;
               virtual float render(bool only_calculate_height_dont_render=false) override;
               static bool multiline_text_draw_callback(int line_num=0, const char* line=nullptr, int size=0, void* extra=nullptr);
               int count_num_lines_will_render(ALLEGRO_FONT* font=nullptr, float max_width=0.0f, std::string text="[unset-text]");
            };
         }
      }
   }
}



