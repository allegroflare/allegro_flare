#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Layouts/Elements/Text.hpp>
#include <allegro5/allegro_font.h>
#include <map>
#include <string>


namespace AllegroFlare
{
   namespace Layouts
   {
      class Text
      {
      public:
         static constexpr char* DEFAULT_PRIM_MESH_ATLAS_FILENAME = (char*)"ascii_glyphs_12x16-07.png";

      private:
         AllegroFlare::FontBin* font_bin;
         std::string tmj_filename;
         float layout_width;
         float layout_height;
         std::map<std::string, AllegroFlare::Layouts::Elements::Text> text_slots;
         std::map<std::string, std::string> text_data;
         int scale;
         static int _multiline_text_line_number;
         bool initialized;
         ALLEGRO_FONT* obtain_font(int font_size=-18);
         ALLEGRO_FONT* obtain_custom_font(std::string font_family="[unset-font_family]", int font_size=-18);

      protected:


      public:
         Text(AllegroFlare::FontBin* font_bin=nullptr, std::string tmj_filename="[unset-tmj_filename]", std::map<std::string, AllegroFlare::Layouts::Elements::Text> text_slots={});
         ~Text();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_tmj_filename(std::string tmj_filename);
         void set_text_slots(std::map<std::string, AllegroFlare::Layouts::Elements::Text> text_slots);
         void set_scale(int scale);
         std::map<std::string, std::string> get_text_data() const;
         int get_scale() const;
         bool get_initialized() const;
         float get_layout_width();
         float get_layout_height();
         void initialize();
         void set_text_data(std::map<std::string, std::string> text_data={});
         void render();
         void render_debug();
         bool compare_maps(std::map<std::string, std::string> map1={}, std::map<std::string, std::string> map2={});
         std::string lookup_font_identifier_by_family(std::string font_family="[unset-font_family]");
         static bool multiline_text_draw_callback(int line_num=0, const char* line=nullptr, int size=0, void* extra=nullptr);
         int count_num_lines_will_render(ALLEGRO_FONT* font=nullptr, float max_width=0.0f, std::string* text=nullptr);
      };
   }
}



