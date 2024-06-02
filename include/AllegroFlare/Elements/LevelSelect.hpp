#pragma once


#include <AllegroFlare/Elements/LevelSelect.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <functional>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      class LevelSelect
      {
      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::FontBin* font_bin;
         std::vector<std::pair<std::string, std::string>> levels_list;
         std::function<void(AllegroFlare::Elements::LevelSelect*, void*)> on_menu_choice_callback_func;
         void* on_menu_choice_callback_func_user_data;
         AllegroFlare::Placement2D place;
         int cursor_x;
         int cursor_y;
         int selection_box_width;
         int selection_box_height;
         int selection_box_spacing_x;
         int selection_box_spacing_y;
         int num_columns;
         int num_rows;
         bool drawing_backfill_and_frame;
         bool drawing_title_text;
         bool ignore_on_invalid_selection;
         ALLEGRO_COLOR opaquify(ALLEGRO_COLOR color={0,0,0,0});
         ALLEGRO_COLOR change_a(ALLEGRO_COLOR color={0,0,0,0}, float alpha=1.0f);
         void draw_backfill_and_frame();
         void draw_level_select_title_text();
         void draw_level_select_boxes_and_cursor();
         bool has_valid_size();
         void draw_selection_cursor(float x=0.0f, float y=0.0f);
         void draw_level_list_item_box(float x=0.0f, float y=0.0f, float w=1.0f, float h=1.0f, std::string label="[unlabeled]");
         ALLEGRO_FONT* obtain_title_font();
         ALLEGRO_FONT* obtain_level_label_font();

      protected:


      public:
         LevelSelect(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::FontBin* font_bin=nullptr, std::vector<std::pair<std::string, std::string>> levels_list={});
         ~LevelSelect();

         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_levels_list(std::vector<std::pair<std::string, std::string>> levels_list);
         void set_on_menu_choice_callback_func(std::function<void(AllegroFlare::Elements::LevelSelect*, void*)> on_menu_choice_callback_func);
         void set_on_menu_choice_callback_func_user_data(void* on_menu_choice_callback_func_user_data);
         void set_selection_box_width(int selection_box_width);
         void set_selection_box_height(int selection_box_height);
         void set_selection_box_spacing_x(int selection_box_spacing_x);
         void set_selection_box_spacing_y(int selection_box_spacing_y);
         void set_num_columns(int num_columns);
         void set_num_rows(int num_rows);
         void set_drawing_backfill_and_frame(bool drawing_backfill_and_frame);
         void set_drawing_title_text(bool drawing_title_text);
         void set_ignore_on_invalid_selection(bool ignore_on_invalid_selection);
         std::vector<std::pair<std::string, std::string>> get_levels_list() const;
         std::function<void(AllegroFlare::Elements::LevelSelect*, void*)> get_on_menu_choice_callback_func() const;
         void* get_on_menu_choice_callback_func_user_data() const;
         AllegroFlare::Placement2D get_place() const;
         int get_cursor_x() const;
         int get_cursor_y() const;
         int get_selection_box_width() const;
         int get_selection_box_height() const;
         int get_selection_box_spacing_x() const;
         int get_selection_box_spacing_y() const;
         int get_num_columns() const;
         int get_num_rows() const;
         bool get_drawing_backfill_and_frame() const;
         bool get_drawing_title_text() const;
         bool get_ignore_on_invalid_selection() const;
         void disable_drawing_backfill_and_frame();
         void disable_drawing_title_text();
         void enable_drawing_backfill_and_frame();
         void enable_drawing_title_text();
         void render();
         void move_cursor_up();
         void move_cursor_down();
         void move_cursor_left();
         void move_cursor_right();
         bool list_is_empty();
         void activate_selected_menu_option();
         std::string infer_current_menu_option_value();
         int infer_cursor_position();
         bool cursor_selection_is_valid();
      };
   }
}



