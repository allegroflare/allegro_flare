#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/TextFormatters/Basic.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <functional>
#include <set>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace TextFormatters
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
         bool draw_unrendered_pretext;
         std::function<void(AllegroFlare::TextFormatters::Basic*, std::string, void*)> on_operational_chunk_func;
         void* on_operational_chunk_func_user_data;
         ALLEGRO_COLOR render_state__text_color;
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
         void set_draw_unrendered_pretext(bool draw_unrendered_pretext);
         void set_on_operational_chunk_func(std::function<void(AllegroFlare::TextFormatters::Basic*, std::string, void*)> on_operational_chunk_func);
         void set_on_operational_chunk_func_user_data(void* on_operational_chunk_func_user_data);
         void set_render_state__text_color(ALLEGRO_COLOR render_state__text_color);
         std::string get_text() const;
         std::string get_font_name() const;
         int get_font_size() const;
         float get_x() const;
         float get_y() const;
         float get_max_text_box_width() const;
         int get_num_revealed_characters() const;
         bool get_draw_unrendered_pretext() const;
         std::function<void(AllegroFlare::TextFormatters::Basic*, std::string, void*)> get_on_operational_chunk_func() const;
         void* get_on_operational_chunk_func_user_data() const;
         ALLEGRO_COLOR get_render_state__text_color() const;
         static bool line_callback(int line_num=0, const char* line=nullptr, int size=0, void* extra=nullptr);
         std::set<int> calculate_line_breaks(std::string raw_text_source="[unset-raw_text_source]");
         static std::vector<std::pair<bool, std::string>> parse_into_chunks(std::string raw_text_source="[unset-raw_text_source]");
         static void default_on_operational_chunk_func(AllegroFlare::TextFormatters::Basic* text_formatter=nullptr, std::string text="[unset-text]", void* user_data=nullptr);
         static std::string collate_printable_text_only(std::string raw_text_source="[unset-raw_text_source]");
         void render();
      };
   }
}



