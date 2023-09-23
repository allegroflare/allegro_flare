#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/ListBox.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
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
         static constexpr ALLEGRO_COLOR DEFAULT_SELECTION_COLOR = ALLEGRO_COLOR{0.5f, 1.0f, 0.83f, 1.0f};

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
         ALLEGRO_COLOR text_color_selected;
         ALLEGRO_COLOR text_color_not_selected;
         bool show_frame_around_selection;
         ALLEGRO_COLOR selection_frame_color;
         void draw_choices_with_cursor_and_current_selection();
         ALLEGRO_FONT* obtain_text_font();
         std::vector<std::pair<std::string, std::string>> obtain_list_box_items();
         int obtain_list_box_cursor_position();
         std::string concat_text(std::string source_text="", int length=0);

      protected:


      public:
         ListBoxRenderer(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::Elements::ListBox* list_box=nullptr, float width=(1920/3.0f), float height=(1080/5.0f), std::string font_name=DEFAULT_FONT_NAME, int font_size=DEFAULT_FONT_SIZE, float text_padding_x=52.0f, float text_padding_y=40.0f, ALLEGRO_COLOR text_color_selected=DEFAULT_SELECTION_COLOR, ALLEGRO_COLOR text_color_not_selected=ALLEGRO_COLOR{1, 1, 1, 1}, bool show_frame_around_selection=true, ALLEGRO_COLOR selection_frame_color=DEFAULT_SELECTION_COLOR);
         ~ListBoxRenderer();

         void set_width(float width);
         void set_height(float height);
         void set_font_name(std::string font_name);
         void set_font_size(int font_size);
         void set_text_padding_x(float text_padding_x);
         void set_text_padding_y(float text_padding_y);
         void set_text_color_selected(ALLEGRO_COLOR text_color_selected);
         void set_text_color_not_selected(ALLEGRO_COLOR text_color_not_selected);
         void set_show_frame_around_selection(bool show_frame_around_selection);
         void set_selection_frame_color(ALLEGRO_COLOR selection_frame_color);
         float get_width() const;
         float get_height() const;
         std::string get_font_name() const;
         int get_font_size() const;
         float get_text_padding_x() const;
         float get_text_padding_y() const;
         ALLEGRO_COLOR get_text_color_selected() const;
         ALLEGRO_COLOR get_text_color_not_selected() const;
         bool get_show_frame_around_selection() const;
         ALLEGRO_COLOR get_selection_frame_color() const;
         void render();
         float calculate_list_item_max_width();
         float calculate_line_height();
         float calculate_item_spacing_padding();
         float calculate_content_height();
         void set_height_to_fit_content();
         static bool multiline_text_draw_callback(int line_number=0, const char* line=nullptr, int size=0, void* extra=nullptr);
         int count_num_lines_will_render(ALLEGRO_FONT* font=nullptr, float max_width=0.0f, std::string text="[unset-text]");
      };
   }
}



