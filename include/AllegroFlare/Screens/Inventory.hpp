#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Inventory.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <map>
#include <string>
#include <utility>


namespace AllegroFlare
{
   namespace Screens
   {
      class Inventory
      {
      private:
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::Inventory* af_inventory;
         AllegroFlare::Placement2D place;
         int cursor_x;
         int cursor_y;
         int num_columns;
         int num_rows;
         bool active;
         float details_reveal_counter;
         int details_num_revealed_characters;
         std::map<int, std::tuple<std::string, std::string, std::string>> inventory_index;
         float reveal_counter;
         int item_in_details_pane;

      public:
         Inventory(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::Inventory* af_inventory=nullptr);
         ~Inventory();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
         void set_af_inventory(AllegroFlare::Inventory* af_inventory);
         AllegroFlare::Placement2D get_place();
         int get_cursor_x();
         int get_cursor_y();
         bool get_active();
         void update();
         void activate();
         void deactivate();
         void set_details_pane();
         ALLEGRO_COLOR opaquify(ALLEGRO_COLOR color={0,0,0,0});
         ALLEGRO_COLOR change_a(ALLEGRO_COLOR color={0,0,0,0}, float alpha=1.0f);
         float inv_reveal_counter();
         void render();
         void draw_backframe();
         void draw_inventory_title_text();
         void draw_inventory_boxes_and_elevated_item_selection();
         void draw_details_frame();
         void move_cursor_up();
         void move_cursor_down();
         void move_cursor_left();
         void move_cursor_right();
         bool show();
         bool hide();
         bool has_valid_size();
         void draw_item_selection_cursor(float x=0.0f, float y=0.0f);
         void draw_inventory_item_box(float x=0.0f, float y=0.0f, int item=0);
         std::tuple<std::string, std::string, std::string> get_item_definition(int index=0);
         ALLEGRO_FONT* obtain_title_font();
         ALLEGRO_FONT* obtain_description_font();
         ALLEGRO_FONT* obtain_item_name_font();
         ALLEGRO_FONT* obtain_details_header_font();
         static std::map<int, std::tuple<std::string, std::string, std::string>> build_inventory_index();
         std::string concat_text(std::string source_text="", int length=0);
      };
   }
}



