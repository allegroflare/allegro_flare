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
         static std::set<int> _line_break_indices;
         ALLEGRO_FONT* obtain_font();

      protected:


      public:
         Basic(AllegroFlare::FontBin* font_bin=nullptr, std::string text="[unset-text]");
         ~Basic();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_text(std::string text);
         std::string get_text() const;
         static bool line_callback(int line_num=0, const char* line=nullptr, int size=0, void* extra=nullptr);
         std::set<int> calculate_line_breaks(std::string raw_text_source="[unset-raw_text_source]");
         static std::vector<std::pair<bool, std::string>> parse_into_chunks(std::string raw_text_source="[unset-raw_text_source]");
         void render();
      };
   }
}



