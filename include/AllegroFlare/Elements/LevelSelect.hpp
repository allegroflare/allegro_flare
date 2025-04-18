#pragma once


#include <AllegroFlare/Elements/LevelSelect.hpp>
#include <AllegroFlare/Elements/LevelSelectItemBoxRenderParams.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <cstdint>
#include <functional>
#include <set>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      class LevelSelect
      {
      public:
         static constexpr int DEFAULT_FRAME_WIDTH = 1300;
         static constexpr int DEFAULT_FRAME_HEIGHT = 800;

      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::FontBin* font_bin;
         std::vector<std::pair<std::string, std::string>> levels_list;
         std::set<std::string> locked_list;
         std::set<std::string> completed_list;
         std::function<void(AllegroFlare::Elements::LevelSelect*, void*)> on_menu_choice_callback_func;
         void* on_menu_choice_callback_func_user_data;
         std::function<void(AllegroFlare::Elements::LevelSelect*, void*, AllegroFlare::Elements::LevelSelectItemBoxRenderParams*)> on_draw_level_list_item_box_func;
         void* on_draw_level_list_item_box_func_user_data;
         AllegroFlare::Placement2D place;
         int cursor_x;
         int cursor_y;
         std::string title_text;
         std::string title_font_name;
         int title_font_size;
         ALLEGRO_COLOR title_color;
         float title_align;
         float title_position_x;
         float title_position_y;
         float title_in_container_alignment_x;
         float title_in_container_alignment_y;
         bool title_text_position_is_relative_to_frame;
         int selection_box_width;
         int selection_box_height;
         int selection_box_spacing_x;
         int selection_box_spacing_y;
         int num_columns;
         int num_rows;
         bool hide_title_when_locked;
         bool show_completed_text_on_list_item_box;
         bool drawing_backfill_and_frame;
         bool drawing_title_text;
         bool ignore_on_invalid_selection;
         ALLEGRO_COLOR change_a(ALLEGRO_COLOR color={0,0,0,0}, float alpha=1.0f);
         void draw_backfill_and_frame();
         void draw_level_select_title_text();
         void draw_level_select_boxes_and_cursor();
         bool has_valid_size();
         void draw_selection_cursor(float x=0.0f, float y=0.0f);
         static void default_on_draw_level_list_item_box_func(AllegroFlare::Elements::LevelSelect* level_select_element=nullptr, void* user_data=nullptr, AllegroFlare::Elements::LevelSelectItemBoxRenderParams* render_params=nullptr);
         ALLEGRO_FONT* obtain_title_font();
         ALLEGRO_FONT* obtain_level_label_font();
         ALLEGRO_FONT* obtain_small_label_font();

      protected:


      public:
         LevelSelect(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::FontBin* font_bin=nullptr, std::vector<std::pair<std::string, std::string>> levels_list={}, std::set<std::string> locked_list={}, std::set<std::string> completed_list={});
         ~LevelSelect();

         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_levels_list(std::vector<std::pair<std::string, std::string>> levels_list);
         void set_locked_list(std::set<std::string> locked_list);
         void set_completed_list(std::set<std::string> completed_list);
         void set_on_menu_choice_callback_func(std::function<void(AllegroFlare::Elements::LevelSelect*, void*)> on_menu_choice_callback_func);
         void set_on_menu_choice_callback_func_user_data(void* on_menu_choice_callback_func_user_data);
         void set_on_draw_level_list_item_box_func(std::function<void(AllegroFlare::Elements::LevelSelect*, void*, AllegroFlare::Elements::LevelSelectItemBoxRenderParams*)> on_draw_level_list_item_box_func);
         void set_on_draw_level_list_item_box_func_user_data(void* on_draw_level_list_item_box_func_user_data);
         void set_title_text(std::string title_text);
         void set_title_font_name(std::string title_font_name);
         void set_title_font_size(int title_font_size);
         void set_title_color(ALLEGRO_COLOR title_color);
         void set_title_align(float title_align);
         void set_title_position_x(float title_position_x);
         void set_title_position_y(float title_position_y);
         void set_title_in_container_alignment_x(float title_in_container_alignment_x);
         void set_title_in_container_alignment_y(float title_in_container_alignment_y);
         void set_title_text_position_is_relative_to_frame(bool title_text_position_is_relative_to_frame);
         void set_selection_box_width(int selection_box_width);
         void set_selection_box_height(int selection_box_height);
         void set_selection_box_spacing_x(int selection_box_spacing_x);
         void set_selection_box_spacing_y(int selection_box_spacing_y);
         void set_num_columns(int num_columns);
         void set_num_rows(int num_rows);
         void set_hide_title_when_locked(bool hide_title_when_locked);
         void set_show_completed_text_on_list_item_box(bool show_completed_text_on_list_item_box);
         void set_drawing_backfill_and_frame(bool drawing_backfill_and_frame);
         void set_drawing_title_text(bool drawing_title_text);
         void set_ignore_on_invalid_selection(bool ignore_on_invalid_selection);
         std::vector<std::pair<std::string, std::string>> get_levels_list() const;
         std::set<std::string> get_locked_list() const;
         std::set<std::string> get_completed_list() const;
         std::function<void(AllegroFlare::Elements::LevelSelect*, void*)> get_on_menu_choice_callback_func() const;
         void* get_on_menu_choice_callback_func_user_data() const;
         std::function<void(AllegroFlare::Elements::LevelSelect*, void*, AllegroFlare::Elements::LevelSelectItemBoxRenderParams*)> get_on_draw_level_list_item_box_func() const;
         void* get_on_draw_level_list_item_box_func_user_data() const;
         AllegroFlare::Placement2D get_place() const;
         int get_cursor_x() const;
         int get_cursor_y() const;
         std::string get_title_text() const;
         std::string get_title_font_name() const;
         int get_title_font_size() const;
         ALLEGRO_COLOR get_title_color() const;
         float get_title_align() const;
         float get_title_position_x() const;
         float get_title_position_y() const;
         float get_title_in_container_alignment_x() const;
         float get_title_in_container_alignment_y() const;
         bool get_title_text_position_is_relative_to_frame() const;
         int get_selection_box_width() const;
         int get_selection_box_height() const;
         int get_selection_box_spacing_x() const;
         int get_selection_box_spacing_y() const;
         int get_num_columns() const;
         int get_num_rows() const;
         bool get_hide_title_when_locked() const;
         bool get_show_completed_text_on_list_item_box() const;
         bool get_drawing_backfill_and_frame() const;
         bool get_drawing_title_text() const;
         bool get_ignore_on_invalid_selection() const;
         AllegroFlare::Placement2D &get_place_ref();
         void add_to_locked_list(std::string level_identifier="[unset-level_identifier]");
         void add_to_completed_list(std::string level_identifier="[unset-level_identifier]");
         bool is_locked(std::string level_identifier="[unset-level_identifier]");
         bool is_completed(std::string level_identifier="[unset-level_identifier]");
         bool unlock(std::string level_identifier="[unset-level_identifier]");
         void unlock_all();
         bool mark_as_completed(std::string level_identifier="[unset-level_identifier]");
         static ALLEGRO_COLOR opaquify(ALLEGRO_COLOR color={0,0,0,0}, float opacity=1.0f);
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
         static void draw_unicode_character(ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, int32_t icon=61444, int flags=0, float x=0.0f, float y=0.0f);
         ALLEGRO_FONT* obtain_lock_icon_font();
         ALLEGRO_FONT* obtain_small_lock_icon_font();
      };
   }
}



