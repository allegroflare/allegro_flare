#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/Inventory.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Inventory.hpp>
#include <AllegroFlare/InventoryDictionary.hpp>
#include <AllegroFlare/InventoryIndex.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <functional>
#include <string>
#include <tuple>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      class Inventory
      {
      private:
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::Inventory* af_inventory;
         AllegroFlare::InventoryIndex* inventory_index;
         AllegroFlare::InventoryDictionary* inventory_dictionary;
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::Placement2D place;
         int cursor_x;
         int cursor_y;
         int num_columns;
         int num_rows;
         bool active;
         float details_reveal_counter;
         int details_num_revealed_characters;
         float reveal_counter;
         int item_in_details_pane;
         float item_in_details_pane_set_at;
         float inventory_items_left_padding;
         float inventory_items_top_padding;
         float inventory_items_box_size_x;
         float inventory_items_box_size_y;
         float inventory_items_box_gutter_x;
         float inventory_items_box_gutter_y;
         std::string cursor_move_sound_identifier;
         bool show_background;
         bool show_backframe;
         bool show_title_text;
         std::function<void(AllegroFlare::Elements::Inventory*, void*)> draw_details_pane_func;
         void* draw_details_pane_func_user_data;
         std::function<void(AllegroFlare::Elements::Inventory*, float, float, int, int, int, void*)> draw_inventory_item_func;
         void* draw_inventory_item_func_user_data;
         bool render_selectable_items_before_details_pane;
         std::string inventory_show_sound_identifier;
         std::string inventory_hide_sound_identifier;
         bool sound_is_disabled;
         void set_details_pane();
         ALLEGRO_COLOR opaquify(ALLEGRO_COLOR color={0,0,0,0});
         ALLEGRO_COLOR change_a(ALLEGRO_COLOR color={0,0,0,0}, float alpha=1.0f);
         float inv_reveal_counter();
         void draw_backframe();
         void draw_title_text();
         void draw_inventory_items();
         void draw_inventory_boxes();
         void draw_details_pane();
         bool has_valid_size();
         void draw_inventory_box(float x=0.0f, float y=0.0f);
         void draw_inventory_item(float x=0.0f, float y=0.0f, int item=0);
         void play_move_cursor_sound();
         void play_hide_inventory_sound();
         void play_show_inventory_sound();

      protected:


      public:
         Inventory(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::Inventory* af_inventory=nullptr, AllegroFlare::InventoryIndex* inventory_index=nullptr, AllegroFlare::InventoryDictionary* inventory_dictionary=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr);
         ~Inventory();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
         void set_af_inventory(AllegroFlare::Inventory* af_inventory);
         void set_inventory_index(AllegroFlare::InventoryIndex* inventory_index);
         void set_inventory_dictionary(AllegroFlare::InventoryDictionary* inventory_dictionary);
         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_place(AllegroFlare::Placement2D place);
         void set_inventory_items_left_padding(float inventory_items_left_padding);
         void set_inventory_items_top_padding(float inventory_items_top_padding);
         void set_inventory_items_box_size_x(float inventory_items_box_size_x);
         void set_inventory_items_box_size_y(float inventory_items_box_size_y);
         void set_inventory_items_box_gutter_x(float inventory_items_box_gutter_x);
         void set_inventory_items_box_gutter_y(float inventory_items_box_gutter_y);
         void set_cursor_move_sound_identifier(std::string cursor_move_sound_identifier);
         void set_show_background(bool show_background);
         void set_show_backframe(bool show_backframe);
         void set_show_title_text(bool show_title_text);
         void set_draw_details_pane_func(std::function<void(AllegroFlare::Elements::Inventory*, void*)> draw_details_pane_func);
         void set_draw_details_pane_func_user_data(void* draw_details_pane_func_user_data);
         void set_draw_inventory_item_func(std::function<void(AllegroFlare::Elements::Inventory*, float, float, int, int, int, void*)> draw_inventory_item_func);
         void set_draw_inventory_item_func_user_data(void* draw_inventory_item_func_user_data);
         void set_render_selectable_items_before_details_pane(bool render_selectable_items_before_details_pane);
         void set_inventory_show_sound_identifier(std::string inventory_show_sound_identifier);
         void set_inventory_hide_sound_identifier(std::string inventory_hide_sound_identifier);
         AllegroFlare::Placement2D get_place() const;
         int get_cursor_x() const;
         int get_cursor_y() const;
         int get_num_columns() const;
         int get_num_rows() const;
         bool get_active() const;
         float get_details_reveal_counter() const;
         int get_details_num_revealed_characters() const;
         float get_reveal_counter() const;
         int get_item_in_details_pane() const;
         float get_item_in_details_pane_set_at() const;
         float get_inventory_items_left_padding() const;
         float get_inventory_items_top_padding() const;
         float get_inventory_items_box_size_x() const;
         float get_inventory_items_box_size_y() const;
         float get_inventory_items_box_gutter_x() const;
         float get_inventory_items_box_gutter_y() const;
         std::string get_cursor_move_sound_identifier() const;
         bool get_show_background() const;
         bool get_show_backframe() const;
         bool get_show_title_text() const;
         std::function<void(AllegroFlare::Elements::Inventory*, void*)> get_draw_details_pane_func() const;
         void* get_draw_details_pane_func_user_data() const;
         std::function<void(AllegroFlare::Elements::Inventory*, float, float, int, int, int, void*)> get_draw_inventory_item_func() const;
         void* get_draw_inventory_item_func_user_data() const;
         bool get_render_selectable_items_before_details_pane() const;
         std::string get_inventory_show_sound_identifier() const;
         std::string get_inventory_hide_sound_identifier() const;
         bool get_sound_is_disabled() const;
         AllegroFlare::Placement2D &get_place_ref();
         void update();
         void activate();
         void deactivate();
         void refresh();
         bool show();
         bool hide();
         void toggle_show_hide();
         void move_cursor_up();
         void move_cursor_down();
         void move_cursor_left();
         void move_cursor_right();
         float calc_details_header_reveal_x_offset();
         ALLEGRO_COLOR calc_details_header_reveal_color();
         void disable_sound();
         void enable_sound();
         bool is_sound_disabled();
         bool is_sound_enabled();
         void set_num_columns(int num_columns=1);
         void set_num_rows(int num_rows=1);
         void render();
         void draw_selectable_items();
         void draw_background();
         static std::vector<int> sort_inventory_items(std::vector<int> items_in_inventory={});
         static std::vector<int> make_sorted_list_unique(std::vector<int> items_in_inventory={});
         int infer_item_id_at_position(int inventory_position=0);
         void draw_details_item_name(float x=0, float y=0, ALLEGRO_FONT* font=nullptr);
         void draw_details_item_description(float x=0, float y=0, float width=1, ALLEGRO_FONT* font=nullptr);
         void draw_item_selection_cursor();
         std::tuple<std::string, std::string, std::string> get_item_definition(int index=0);
         ALLEGRO_FONT* obtain_title_font();
         ALLEGRO_FONT* obtain_description_font();
         ALLEGRO_FONT* obtain_item_details_font();
         ALLEGRO_FONT* obtain_item_count_font();
         ALLEGRO_FONT* obtain_item_name_font();
         ALLEGRO_FONT* obtain_details_header_font();
         float infer_item_boxes_width();
         float infer_item_boxes_height();
         void play_sound(std::string sound_identifier="[unset-play_sound]");
         static AllegroFlare::InventoryIndex* create_placeholder_inventory_index();
         static std::string concat_text(std::string source_text="", int length=0);
      };
   }
}



