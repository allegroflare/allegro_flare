#pragma once


#include <AllegroFlare/Elements/Base.hpp>
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
      class MultiList : public AllegroFlare::Elements::Base
      {
      private:
         AllegroFlare::FontBin* font_bin;
         int cursor_x;
         int cursor_y;
         std::vector<std::vector<std::pair<std::string, std::string>>> lists;
         std::vector<int> list_cursor_positions;
         AllegroFlare::Elements::SelectionCursorBox selection_cursor_box;
         float list_item_width;
         float list_item_height;
         float list_item_margin_x;
         float list_item_margin_y;
         bool wrap_cursor_horizontally;
         bool wrap_cursors_vertically;
         bool move_cursor_to_active_item_when_entering_list;
         bool initialized;
         void move_cursor_box_position_to_cursor_location();
         void draw_list_item(float x=0.0f, float y=0.0f, float width=480.0f, float height=48.0f, std::string text="[unset-text]", bool is_selected=false);
         ALLEGRO_FONT* obtain_small_hud_font();
         ALLEGRO_FONT* obtain_medium_hud_font();

      protected:


      public:
         MultiList();
         virtual ~MultiList();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_wrap_cursor_horizontally(bool wrap_cursor_horizontally);
         void set_wrap_cursors_vertically(bool wrap_cursors_vertically);
         void set_move_cursor_to_active_item_when_entering_list(bool move_cursor_to_active_item_when_entering_list);
         int get_cursor_x() const;
         int get_cursor_y() const;
         float get_list_item_width() const;
         float get_list_item_height() const;
         bool get_wrap_cursor_horizontally() const;
         bool get_wrap_cursors_vertically() const;
         bool get_move_cursor_to_active_item_when_entering_list() const;
         bool get_initialized() const;
         void set_list_item_width(int list_item_width=48.0f);
         void set_list_item_height(int list_item_height=48.0f);
         void initialize();
         bool move_cursor_up();
         bool move_cursor_down();
         bool move_cursor_left();
         bool move_cursor_right();
         void set_lists(std::vector<std::vector<std::pair<std::string, std::string>>> lists={});
         void activate_selection_at_current_cursor_position();
         void set_cursor_position(int cursor_x=0, int cursor_y=0);
         float calculate_width();
         float calculate_cursor_real_x();
         float calculate_cursor_real_y();
         virtual void render() override;
      };
   }
}



