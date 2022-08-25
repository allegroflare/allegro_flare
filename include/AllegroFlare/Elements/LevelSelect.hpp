#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
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
         AllegroFlare::Placement2D place;
         int cursor_x;
         int cursor_y;
         int selection_box_width;
         int selection_box_height;
         int selection_box_spacing_x;
         int selection_box_spacing_y;
         int num_columns;
         int num_rows;

      public:
         LevelSelect(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::FontBin* font_bin=nullptr, std::vector<std::pair<std::string, std::string>> levels_list={});
         ~LevelSelect();

         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_levels_list(std::vector<std::pair<std::string, std::string>> levels_list);
         void set_num_columns(int num_columns);
         void set_num_rows(int num_rows);
         AllegroFlare::Placement2D get_place() const;
         int get_cursor_x() const;
         int get_cursor_y() const;
         int get_selection_box_width() const;
         int get_selection_box_height() const;
         int get_selection_box_spacing_x() const;
         int get_selection_box_spacing_y() const;
         int get_num_columns() const;
         int get_num_rows() const;
         ALLEGRO_COLOR opaquify(ALLEGRO_COLOR color={0,0,0,0});
         ALLEGRO_COLOR change_a(ALLEGRO_COLOR color={0,0,0,0}, float alpha=1.0f);
         void render();
         void draw_backfill_and_frame();
         void draw_level_select_title_text();
         void draw_level_select_boxes_and_cursor();
         void move_cursor_up();
         void move_cursor_down();
         void move_cursor_left();
         void move_cursor_right();
         bool has_valid_size();
         bool list_is_empty();
         void draw_selection_cursor(float x=0.0f, float y=0.0f);
         void draw_level_list_item_box(float x=0.0f, float y=0.0f, float w=1.0f, float h=1.0f, std::string label="[unlabeled]");
         void activate_selected_menu_option();
         std::string infer_current_menu_option_value();
         ALLEGRO_FONT* obtain_title_font();
         ALLEGRO_FONT* obtain_description_font();
         ALLEGRO_FONT* obtain_item_name_font();
      };
   }
}



