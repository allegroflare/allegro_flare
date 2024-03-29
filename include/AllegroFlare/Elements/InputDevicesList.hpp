#pragma once


#include <AllegroFlare/Elements/Button.hpp>
#include <AllegroFlare/Elements/SelectionCursorBox.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/PhysicalInputDevices/Base.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <cstdint>
#include <string>
#include <tuple>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      class InputDevicesList
      {
      public:
         static constexpr uint32_t SCROLLBAR_MOVEMENT_NONE = 0;
         static constexpr uint32_t SCROLLBAR_MOVEMENT_FOLLOW_PROPORTIONAL = 1;
         static constexpr float DEFAULT_SCROLLBAR_REPOSITION_MULTIPLIER = 0.1f;

      private:
         enum connection_status_t : uint32_t
         {
            CONNECTION_STATUS_UNDEFINED = 0,
            CONNECTION_STATUS_CONNECTED,
            CONNECTION_STATUS_DISCONNECTED,
         };
         AllegroFlare::FontBin* font_bin;
         std::vector<std::tuple<AllegroFlare::PhysicalInputDevices::Base*, uint32_t, std::string, std::string>> input_devices;
         float list_item_box_width;
         float list_item_box_height;
         int surface_width;
         int surface_height;
         int cursor_pos;
         AllegroFlare::Elements::SelectionCursorBox selection_cursor_box;
         AllegroFlare::Elements::Button selection_cursor_button;
         float scrollbar_position;
         float scrollbar_position_destination;
         uint32_t scrollbar_movement_mode;
         float box_gutter_y;
         float scrollbar_reposition_multiplier;
         bool initialized;
         void move_selection_cursor_box_to_current_cursor_location();
         AllegroFlare::Vec2D build_selection_cursor_box_position_of_current_cursor_pos();
         AllegroFlare::Vec2D build_selection_cursor_button_position_of_current_cursor_pos();
         float build_scrollbar_position_at_current_cursor_pos();
         int count_num_input_devices_connected();
         int count_num_input_devices_disconnected();
         void draw_header_title_backfill();
         int count_num_input_devices();
         std::string build_input_devices_count_string();
         void draw_input_devices_list_title_text_and_completed_title_text();
         float infer_container_height();
         float infer_list_item_y_spacing();
         float infer_container_contents_height_for_n_elements(int num_elements=0);
         float infer_container_contents_height();
         float infer_container_scroll_range();
         void limit_scrollbar_position();
         void draw_input_devices_list_items_and_scrollbar();
         void draw_input_device_box(float x=0.0f, float y=0.0f, AllegroFlare::PhysicalInputDevices::Base* physical_input_device=nullptr, uint32_t connection_status=CONNECTION_STATUS_UNDEFINED, std::string title="[unset-title]", std::string device_id="[unset-device_id]");
         int32_t infer_icon_character_for_physical_input_device(AllegroFlare::PhysicalInputDevices::Base* physical_input_device=nullptr);
         ALLEGRO_COLOR infer_icon_color_by_connection_status(uint32_t connection_status=CONNECTION_STATUS_UNDEFINED, ALLEGRO_COLOR icon_locked_color=ALLEGRO_COLOR{1, 1, 1, 1}, ALLEGRO_COLOR icon_hidden_color=ALLEGRO_COLOR{1, 1, 1, 1}, ALLEGRO_COLOR icon_achieved_color=ALLEGRO_COLOR{1, 1, 1, 1});
         bool current_selected_item_is_connected();
         std::string filter_item_title_through_connection_status(std::string title="[unset-title]", uint32_t connection_status=CONNECTION_STATUS_UNDEFINED);
         std::string build_item_description(std::string device_id="", uint32_t connection_status=CONNECTION_STATUS_UNDEFINED);
         ALLEGRO_FONT* obtain_title_font();
         ALLEGRO_FONT* obtain_item_title_font();
         ALLEGRO_FONT* obtain_item_description_font();
         ALLEGRO_FONT* obtain_icon_font();
         void draw_unicode_character(ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, int x=0, int y=0, uint32_t icon=61444, int flags=0);

      protected:


      public:
         InputDevicesList(AllegroFlare::FontBin* font_bin=nullptr, std::vector<std::tuple<AllegroFlare::PhysicalInputDevices::Base*, uint32_t, std::string, std::string>> input_devices={}, float list_item_box_width=960.0f, float list_item_box_height=148.0f);
         ~InputDevicesList();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_list_item_box_width(float list_item_box_width);
         void set_list_item_box_height(float list_item_box_height);
         void set_surface_width(int surface_width);
         void set_surface_height(int surface_height);
         void set_box_gutter_y(float box_gutter_y);
         std::vector<std::tuple<AllegroFlare::PhysicalInputDevices::Base*, uint32_t, std::string, std::string>> get_input_devices() const;
         float get_list_item_box_width() const;
         float get_list_item_box_height() const;
         int get_surface_width() const;
         int get_surface_height() const;
         int get_cursor_pos() const;
         float get_scrollbar_position() const;
         float get_scrollbar_position_destination() const;
         float get_box_gutter_y() const;
         float get_scrollbar_reposition_multiplier() const;
         bool get_initialized() const;
         void set_input_devices(std::vector<std::tuple<AllegroFlare::PhysicalInputDevices::Base*, uint32_t, std::string, std::string>> input_devices={});
         void initialize();
         bool move_cursor_up();
         bool move_cursor_down();
         float infer_list_item_spacing_y();
         bool scrollbar_movement_mode_is_follow_proportional();
         void update();
         void render();
         void move_scrollbar_position(float distance_y=0.0f);
         void set_scrollbar_position(float scrollbar_position=0.0f);
         void set_scrollbar_position_to_max();
         float infer_scrollbar_max_position();
         bool scrollbar_is_autohidden_because_list_contents_is_smaller_than_the_container();
         bool list_contents_is_smaller_than_the_container();
         static std::vector<std::tuple<AllegroFlare::PhysicalInputDevices::Base*, uint32_t, std::string, std::string>> build_placeholder_input_devices();
         void draw_scrollarea_contents();
      };
   }
}



