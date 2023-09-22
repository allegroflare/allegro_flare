#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/ListBox.hpp>
#include <AllegroFlare/Elements/SelectionCursorBox.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      class ListBoxRenderer
      {
      public:
         static constexpr char* DEFAULT_FONT_NAME = (char*)"Inter-Regular.ttf";
         static constexpr int DEFAULT_FONT_SIZE = -36;

      private:
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::Elements::ListBox* list_box;
         float width;
         float height;
         std::string font_name;
         int font_size;
         float text_padding_x;
         float text_padding_y;
         AllegroFlare::Elements::SelectionCursorBox selection_cursor_box;
         void draw_choices_with_cursor_and_current_selection();
         ALLEGRO_FONT* obtain_dialog_font();
         std::vector<std::pair<std::string, std::string>> obtain_list_box_items();
         int obtain_list_box_cursor_position();
         std::string concat_text(std::string source_text="", int length=0);

      protected:


      public:
         ListBoxRenderer(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::Elements::ListBox* list_box=nullptr, float width=(1920/3.0f), float height=(1080/5.0f), std::string font_name=DEFAULT_FONT_NAME, int font_size=DEFAULT_FONT_SIZE, float text_padding_x=52.0f, float text_padding_y=40.0f);
         ~ListBoxRenderer();

         void set_width(float width);
         void set_height(float height);
         void set_font_name(std::string font_name);
         void set_font_size(int font_size);
         void set_text_padding_x(float text_padding_x);
         void set_text_padding_y(float text_padding_y);
         float get_width() const;
         float get_height() const;
         std::string get_font_name() const;
         int get_font_size() const;
         float get_text_padding_x() const;
         float get_text_padding_y() const;
         void render();
         static bool multiline_text_draw_callback(int line_number=0, const char* line=nullptr, int size=0, void* extra=nullptr);
         int count_num_lines_will_render(ALLEGRO_FONT* font=nullptr, float max_width=0.0f, std::string text="[unset-text]");
      };
   }
}



