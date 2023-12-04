#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/WorldMaps/Maps/Basic.hpp>
#include <allegro5/allegro_font.h>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      class WorldMapViewer
      {
      public:
         static constexpr float DEFAULT_CAMERA_RANGE_X1 = -1920/2;
         static constexpr float DEFAULT_CAMERA_RANGE_X2 = 1920/2;
         static constexpr float DEFAULT_CAMERA_RANGE_Y1 = -1080/2;
         static constexpr float DEFAULT_CAMERA_RANGE_Y2 = 1080/2;

      private:
         enum State
         {
            STATE_UNDEF = 0,
            STATE_PLAYER_CONTROLLING,
            STATE_REPOSITIONING_CURSOR,
         };
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::Placement2D map_view_place;
         AllegroFlare::WorldMaps::Maps::Basic* map;
         AllegroFlare::Placement2D map_placement;
         int current_page_index_num;
         AllegroFlare::Camera2D document_camera;
         AllegroFlare::Vec2D cursor;
         AllegroFlare::Vec2D target_cursor;
         float cursor_size;
         float cursor_edge_padding;
         float cursor_velocity_magnitude_axis_x;
         float cursor_velocity_magnitude_axis_y;
         float cursor_max_velocity;
         float document_camera_target_zoom;
         std::vector<float> document_camera_zoom_levels;
         int document_camera_zoom_level_cursor;
         bool wrap_zoom;
         float camera_velocity_magnitude_axis_x;
         float camera_velocity_magnitude_axis_y;
         float camera_range_x1;
         float camera_range_y1;
         float camera_range_x2;
         float camera_range_y2;
         float camera_max_velocity;
         uint32_t state;
         bool state_is_busy;
         float state_changed_at;
         bool initialized;
         void fit_and_position_map();
         void unset_camera_moving();
         void unset_cursor_moving();
         void render_map();
         void render_page_numbers();
         void render_coordinates();
         ALLEGRO_FONT* obtain_font();
         ALLEGRO_FONT* obtain_small_ui_font();

      protected:


      public:
         WorldMapViewer(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr);
         ~WorldMapViewer();

         void set_map_view_place(AllegroFlare::Placement2D map_view_place);
         void set_cursor(AllegroFlare::Vec2D cursor);
         void set_target_cursor(AllegroFlare::Vec2D target_cursor);
         void set_cursor_size(float cursor_size);
         void set_cursor_edge_padding(float cursor_edge_padding);
         void set_cursor_velocity_magnitude_axis_x(float cursor_velocity_magnitude_axis_x);
         void set_cursor_velocity_magnitude_axis_y(float cursor_velocity_magnitude_axis_y);
         void set_cursor_max_velocity(float cursor_max_velocity);
         void set_wrap_zoom(bool wrap_zoom);
         void set_camera_velocity_magnitude_axis_x(float camera_velocity_magnitude_axis_x);
         void set_camera_velocity_magnitude_axis_y(float camera_velocity_magnitude_axis_y);
         void set_camera_range_x1(float camera_range_x1);
         void set_camera_range_y1(float camera_range_y1);
         void set_camera_range_x2(float camera_range_x2);
         void set_camera_range_y2(float camera_range_y2);
         void set_camera_max_velocity(float camera_max_velocity);
         AllegroFlare::BitmapBin* get_bitmap_bin() const;
         AllegroFlare::FontBin* get_font_bin() const;
         AllegroFlare::Placement2D get_map_view_place() const;
         AllegroFlare::WorldMaps::Maps::Basic* get_map() const;
         AllegroFlare::Placement2D get_map_placement() const;
         AllegroFlare::Vec2D get_cursor() const;
         AllegroFlare::Vec2D get_target_cursor() const;
         float get_cursor_size() const;
         float get_cursor_edge_padding() const;
         float get_cursor_velocity_magnitude_axis_x() const;
         float get_cursor_velocity_magnitude_axis_y() const;
         float get_cursor_max_velocity() const;
         bool get_wrap_zoom() const;
         float get_camera_velocity_magnitude_axis_x() const;
         float get_camera_velocity_magnitude_axis_y() const;
         float get_camera_range_x1() const;
         float get_camera_range_y1() const;
         float get_camera_range_x2() const;
         float get_camera_range_y2() const;
         float get_camera_max_velocity() const;
         uint32_t get_state() const;
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void initialize();
         void fit_camera_range_to_map_dimensions();
         void reset();
         void reset_document_camera();
         void reset_document_camera_range_to_defaults();
         void on_switch_in();
         void on_switch_out();
         bool cursor_control_is_user();
         void step_zoom_in();
         void step_zoom_out();
         void set_camera_moving_up();
         void set_camera_moving_down();
         void unset_camera_moving_vertical();
         void set_camera_moving_left();
         void set_camera_moving_right();
         void unset_camera_moving_horizontal();
         void set_cursor_moving_up();
         void set_cursor_moving_down();
         void unset_cursor_moving_vertical();
         void set_cursor_moving_left();
         void set_cursor_moving_right();
         void unset_cursor_moving_horizontal();
         void set_map(AllegroFlare::WorldMaps::Maps::Basic* map=nullptr);
         void snap_cursor_to_origin_or_primary_point_of_interest();
         void move_cursor_to_location(std::string location_id="[unset-location_id]");
         void draw_cursor(float x=0.0f, float y=0.0f);
         bool infer_no_pages_are_present();
         void update();
         void render();
         std::pair<bool, std::string> infer_focused_location_label();
         void render_zoom_scale();
         void draw_empty_state(AllegroFlare::FontBin* font_bin=nullptr, std::string placeholder_text="Empty");
         float calc_zoom_position_relative_min_max();
         void set_state(uint32_t state=STATE_UNDEF, bool override_if_busy=false);
         void update_state(float time_now=al_get_time());
         static bool is_valid_state(uint32_t state=STATE_UNDEF);
         bool is_state(uint32_t possible_state=STATE_UNDEF);
         float infer_current_state_age(float time_now=al_get_time());
      };
   }
}



