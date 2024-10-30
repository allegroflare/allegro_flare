#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <set>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace TextFormatter
   {
      class Basic
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::string text;
         std::string font_name;
         int font_size;
         float x;
         float y;
         float max_text_box_width;
         int num_revealed_characters;
         static std::set<int> _line_break_indices;
         ALLEGRO_FONT* obtain_font();

      protected:


      public:
         Basic(AllegroFlare::FontBin* font_bin=nullptr, std::string text="[unset-text]");
         ~Basic();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_text(std::string text);
         void set_font_name(std::string font_name);
         void set_font_size(int font_size);
         void set_x(float x);
         void set_y(float y);
         void set_max_text_box_width(float max_text_box_width);
         void set_num_revealed_characters(int num_revealed_characters);
         std::string get_text() const;
         std::string get_font_name() const;
         int get_font_size() const;
         float get_x() const;
         float get_y() const;
         float get_max_text_box_width() const;
         int get_num_revealed_characters() const;
         static bool line_callback(int line_num=0, const char* line=nullptr, int size=0, void* extra=nullptr);
         std::set<int> calculate_line_breaks(std::string raw_text_source="[unset-raw_text_source]");
         static std::vector<std::pair<bool, std::string>> parse_into_chunks(std::string raw_text_source="[unset-raw_text_source]");
         static std::string collate_printable_text_only(std::string raw_text_source="[unset-raw_text_source]");
         void render();
      };
   }
}



