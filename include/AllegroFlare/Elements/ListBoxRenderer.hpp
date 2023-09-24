#pragma once


#include <AllegroFlare/BitmapBin.hpp>
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
      class ListBoxRenderer
      {
      public:
         static constexpr char* DEFAULT_FONT_NAME = (char*)"Inter-Regular.ttf";
         static constexpr int DEFAULT_FONT_SIZE = -36;
         static constexpr ALLEGRO_COLOR DEFAULT_SELECTION_COLOR = ALLEGRO_COLOR{0.5f, 1.0f, 0.83f, 1.0f};
         static constexpr ALLEGRO_COLOR DEFAULT_TEXT_NOT_SELECTED_COLOR = ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f};

      private:
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::BitmapBin* bitmap_bin;
         std::vector<std::string> list_items;
         int cursor_position;
         float age;
         float width;
         float height;
         std::string font_name;
         int font_size;
         float text_padding_x;
         float text_padding_y;
         ALLEGRO_COLOR text_color_selected;
         ALLEGRO_COLOR text_color_not_selected;
         ALLEGRO_COLOR frame_backfill_color;
         ALLEGRO_COLOR frame_border_color;
         ALLEGRO_COLOR selection_frame_color;
         void draw_frame();
         void draw_frame_raw();
         void draw_choices_with_cursor_and_current_selection();
         static bool multiline_text_draw_callback(int line_number=0, const char* line=nullptr, int size=0, void* extra=nullptr);
         ALLEGRO_FONT* obtain_text_font();
         std::string concat_text(std::string source_text="", int length=0);

      protected:


      public:
         ListBoxRenderer(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, std::vector<std::string> list_items={});
         ~ListBoxRenderer();

         void set_list_items(std::vector<std::string> list_items);
         void set_cursor_position(int cursor_position);
         void set_age(float age);
         void set_width(float width);
         void set_height(float height);
         void set_font_name(std::string font_name);
         void set_font_size(int font_size);
         void set_text_padding_x(float text_padding_x);
         void set_text_padding_y(float text_padding_y);
         void set_text_color_selected(ALLEGRO_COLOR text_color_selected);
         void set_text_color_not_selected(ALLEGRO_COLOR text_color_not_selected);
         void set_frame_backfill_color(ALLEGRO_COLOR frame_backfill_color);
         void set_frame_border_color(ALLEGRO_COLOR frame_border_color);
         void set_selection_frame_color(ALLEGRO_COLOR selection_frame_color);
         std::vector<std::string> get_list_items() const;
         int get_cursor_position() const;
         float get_age() const;
         float get_width() const;
         float get_height() const;
         std::string get_font_name() const;
         int get_font_size() const;
         float get_text_padding_x() const;
         float get_text_padding_y() const;
         ALLEGRO_COLOR get_text_color_selected() const;
         ALLEGRO_COLOR get_text_color_not_selected() const;
         ALLEGRO_COLOR get_frame_backfill_color() const;
         ALLEGRO_COLOR get_frame_border_color() const;
         ALLEGRO_COLOR get_selection_frame_color() const;
         void render();
         float calculate_list_item_max_width();
         float calculate_line_height();
         float calculate_item_spacing_padding();
         float calculate_content_width();
         float calculate_content_height();
         void set_height_to_fit_content();
         void set_width_to_fit_content_or_max(float max=800);
         std::tuple<float, float, float, float> calculate_dimensions_for_list_item_at_position(int list_item_position=0);
         std::vector<float> calculate_line_widths(ALLEGRO_FONT* font=nullptr, float max_width=0.0f, std::string text="[unset-text]");
         static ALLEGRO_COLOR calculate_DEFAULT_BACKFILL_COLOR();
         static ALLEGRO_COLOR calculate_DEFAULT_BORDER_COLOR();
      };
   }
}



