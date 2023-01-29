#pragma once


#include <AllegroFlare/FontBin.hpp>
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
      class JoystickConfigurationList
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::vector<std::tuple<std::string, uint32_t>> joystick_configuration_mapping;
         float list_item_box_width;
         float list_item_box_height;
         int surface_width;
         int surface_height;
         float scrollbar_position;
         float box_gutter_y;
         void draw_header_title_backfill();
         int count_num_joystick_configuration_mapping();
         void draw_joystick_configuration_mapping_list_title_text();
         float infer_container_height();
         float infer_container_contents_height();
         float infer_container_scroll_range();
         void limit_scrollbar_position();
         void draw_joystick_configuration_mapping_list_items_and_scrollbar();
         void draw_joystick_configuration_item_box(float x=0.0f, float y=0.0f, std::string action_name="[unset-title]", std::string mapped_button_name="[unset-description]");
         int32_t infer_icon_character_by_status(std::string status="[unset-status]");
         ALLEGRO_COLOR infer_icon_color_by_status(std::string status="[unset-status]", ALLEGRO_COLOR icon_locked_color=ALLEGRO_COLOR{1, 1, 1, 1}, ALLEGRO_COLOR icon_hidden_color=ALLEGRO_COLOR{1, 1, 1, 1}, ALLEGRO_COLOR icon_achieved_color=ALLEGRO_COLOR{1, 1, 1, 1});
         std::string filter_item_title_through_status(std::string title="[unset-title]", std::string status="[unset-status]");
         std::string filter_item_description_through_status(std::string description="[unset-title]", std::string status="[unset-status]");
         ALLEGRO_FONT* obtain_title_font();
         ALLEGRO_FONT* obtain_item_title_font();
         ALLEGRO_FONT* obtain_item_description_font();
         ALLEGRO_FONT* obtain_icon_font();
         void draw_unicode_character(ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, int x=0, int y=0, uint32_t icon=61444, int flags=0);

      protected:


      public:
         JoystickConfigurationList(AllegroFlare::FontBin* font_bin=nullptr, std::vector<std::tuple<std::string, uint32_t>> joystick_configuration_mapping={}, float list_item_box_width=740.0f, float list_item_box_height=80.0f);
         ~JoystickConfigurationList();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_joystick_configuration_mapping(std::vector<std::tuple<std::string, uint32_t>> joystick_configuration_mapping);
         void set_list_item_box_width(float list_item_box_width);
         void set_list_item_box_height(float list_item_box_height);
         void set_surface_width(int surface_width);
         void set_surface_height(int surface_height);
         void set_box_gutter_y(float box_gutter_y);
         std::vector<std::tuple<std::string, uint32_t>> get_joystick_configuration_mapping() const;
         float get_list_item_box_width() const;
         float get_list_item_box_height() const;
         int get_surface_width() const;
         int get_surface_height() const;
         float get_scrollbar_position() const;
         float get_box_gutter_y() const;
         void render();
         void move_scrollbar_position(float distance_y=0.0f);
         void set_scrollbar_position(float scrollbar_position=0.0f);
         void set_scrollbar_position_to_max();
         float infer_scrollbar_max_position();
         bool scrollbar_is_autohidden_because_list_contents_is_smaller_than_the_container();
         static std::vector<std::tuple<std::string, uint32_t>> build_placeholder_joystick_configuration_mapping();
      };
   }
}



