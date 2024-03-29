#pragma once


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
      class InputDeviceConfigurationList
      {
      public:
         static constexpr uint32_t STATE_UNDEF = 0;
         static constexpr uint32_t STATE_MOVING_CURSOR = 1;
         static constexpr uint32_t STATE_AWAITING_USER_INPUT_ON_OPTION = 2;
         static constexpr uint32_t SCROLLBAR_MOVEMENT_NONE = 0;
         static constexpr uint32_t SCROLLBAR_MOVEMENT_FOLLOW_PROPORTIONAL = 1;
         static constexpr float DEFAULT_SCROLLBAR_REPOSITION_MULTIPLIER = 0.1f;

      private:
         AllegroFlare::FontBin* font_bin;
         int player_num;
         AllegroFlare::PhysicalInputDevices::Base* physical_input_device;
         std::vector<std::tuple<std::string, uint32_t>> joystick_configuration_mapping;
         float list_item_box_width;
         float list_item_box_height;
         int surface_width;
         int surface_height;
         int cursor_pos;
         AllegroFlare::Elements::SelectionCursorBox selection_cursor_box;
         float scrollbar_position;
         float scrollbar_position_destination;
         float scrollbar_reposition_multiplier;
         uint32_t scrollbar_movement_mode;
         float box_gutter_y;
         uint32_t state;
         bool state_is_busy;
         float state_changed_at;
         bool initialized;
         void move_selection_cursor_box_to_current_cursor_location();
         AllegroFlare::Vec2D build_selection_cursor_box_position_of_current_cursor_pos();
         float build_scrollbar_position_at_current_cursor_pos();
         void draw_header_title_backfill();
         int count_num_joystick_configuration_mapping();
         bool joystick_configuration_mapping_is_empty();
         void draw_joystick_configuration_mapping_list_title_text();
         float infer_container_height();
         float infer_container_contents_height();
         float infer_list_item_height();
         float infer_container_scroll_range();
         void limit_scrollbar_position();
         void draw_joystick_configuration_mapping_list_items_and_scrollbar();
         void draw_joystick_configuration_item_box(float x=0.0f, float y=0.0f, std::string action_name="[unset-title]", std::string mapped_button_name="[unset-description]");
         int32_t infer_icon_character_by_status(std::string status="[unset-status]");
         ALLEGRO_COLOR infer_icon_color_by_status(std::string status="[unset-status]", ALLEGRO_COLOR icon_locked_color=ALLEGRO_COLOR{1, 1, 1, 1}, ALLEGRO_COLOR icon_hidden_color=ALLEGRO_COLOR{1, 1, 1, 1}, ALLEGRO_COLOR icon_achieved_color=ALLEGRO_COLOR{1, 1, 1, 1});
         std::string filter_item_title_through_status(std::string title="[unset-title]", std::string status="[unset-status]");
         std::string filter_item_description_through_status(std::string description="[unset-title]", std::string status="[unset-status]");
         void set_state(uint32_t state=STATE_UNDEF, bool override_if_busy=false);
         ALLEGRO_FONT* obtain_title_font();
         ALLEGRO_FONT* obtain_item_title_font();
         ALLEGRO_FONT* obtain_empty_state_text_font();
         ALLEGRO_FONT* obtain_item_description_font();
         ALLEGRO_FONT* obtain_icon_font();
         void draw_unicode_character(ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, int x=0, int y=0, uint32_t icon=61444, int flags=0);

      protected:


      public:
         InputDeviceConfigurationList(AllegroFlare::FontBin* font_bin=nullptr, int player_num=0, AllegroFlare::PhysicalInputDevices::Base* physical_input_device=nullptr, std::vector<std::tuple<std::string, uint32_t>> joystick_configuration_mapping={}, float list_item_box_width=740.0f, float list_item_box_height=80.0f);
         ~InputDeviceConfigurationList();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_player_num(int player_num);
         void set_list_item_box_width(float list_item_box_width);
         void set_list_item_box_height(float list_item_box_height);
         void set_surface_width(int surface_width);
         void set_surface_height(int surface_height);
         void set_box_gutter_y(float box_gutter_y);
         int get_player_num() const;
         AllegroFlare::PhysicalInputDevices::Base* get_physical_input_device() const;
         std::vector<std::tuple<std::string, uint32_t>> get_joystick_configuration_mapping() const;
         float get_list_item_box_width() const;
         float get_list_item_box_height() const;
         int get_surface_width() const;
         int get_surface_height() const;
         int get_cursor_pos() const;
         float get_scrollbar_position() const;
         float get_scrollbar_position_destination() const;
         float get_scrollbar_reposition_multiplier() const;
         float get_box_gutter_y() const;
         void initialize();
         void update();
         void render();
         void set_joystick_configuration_mapping(std::vector<std::tuple<std::string, uint32_t>> joystick_configuration_mapping={});
         void set_physical_input_device(AllegroFlare::PhysicalInputDevices::Base* physical_input_device=nullptr);
         bool move_cursor_up();
         bool move_cursor_down();
         bool submit_mapping_on_currently_selected_option(uint32_t button_num=0);
         bool select_current_option_for_remapping();
         bool abort_current_option_for_remapping();
         void move_scrollbar_position(float distance_y=0.0f);
         void set_scrollbar_position(float scrollbar_position=0.0f);
         void set_scrollbar_reposition_multiplier(float scrollbar_reposition_multiplier=DEFAULT_SCROLLBAR_REPOSITION_MULTIPLIER);
         void set_scrollbar_position_to_max();
         float infer_scrollbar_max_position();
         bool scrollbar_is_autohidden_because_list_contents_is_smaller_than_the_container();
         static std::vector<std::tuple<std::string, uint32_t>> build_placeholder_joystick_configuration_mapping();
         std::string build_heading_label();
         float infer_list_item_spacing_y();
         bool scrollbar_movement_mode_is_follow_proportional();
         bool is_waiting_user_input_for_remap();
         static bool is_valid_state(uint32_t state=STATE_UNDEF);
         bool is_state(uint32_t possible_state=STATE_UNDEF);
         float infer_current_state_age(float time_now=al_get_time());
      };
   }
}



