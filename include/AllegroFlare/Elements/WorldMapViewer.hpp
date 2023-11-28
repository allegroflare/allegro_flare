#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/WorldMaps/Maps/Basic.hpp>
#include <allegro5/allegro_font.h>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      class WorldMapViewer
      {
      public:
         static constexpr char* TYPE = "Panes/CrimeSummary";

      private:
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::Placement2D place;
         AllegroFlare::WorldMaps::Maps::Basic* map;
         AllegroFlare::Placement2D map_placement;
         int current_page_index_num;
         AllegroFlare::Camera2D document_camera;
         AllegroFlare::Vec2D document_cursor;
         float document_camera_target_zoom;
         std::vector<float> document_camera_zoom_levels;
         int document_camera_zoom_level_cursor;
         float camera_velocity_magnitude_axis_x;
         float camera_velocity_magnitude_axis_y;
         float camera_range_x1;
         float camera_range_y1;
         float camera_range_x2;
         float camera_range_y2;
         float camera_max_velocity;
         bool initialized;
         void fit_and_position_map();
         void render_map();
         void render_page_numbers();
         ALLEGRO_FONT* obtain_font();

      protected:


      public:
         WorldMapViewer(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr);
         ~WorldMapViewer();

         void set_place(AllegroFlare::Placement2D place);
         void set_camera_velocity_magnitude_axis_x(float camera_velocity_magnitude_axis_x);
         void set_camera_velocity_magnitude_axis_y(float camera_velocity_magnitude_axis_y);
         void set_camera_range_x1(float camera_range_x1);
         void set_camera_range_y1(float camera_range_y1);
         void set_camera_range_x2(float camera_range_x2);
         void set_camera_range_y2(float camera_range_y2);
         void set_camera_max_velocity(float camera_max_velocity);
         AllegroFlare::BitmapBin* get_bitmap_bin() const;
         AllegroFlare::FontBin* get_font_bin() const;
         AllegroFlare::Placement2D get_place() const;
         AllegroFlare::WorldMaps::Maps::Basic* get_map() const;
         AllegroFlare::Placement2D get_map_placement() const;
         float get_camera_velocity_magnitude_axis_x() const;
         float get_camera_velocity_magnitude_axis_y() const;
         float get_camera_range_x1() const;
         float get_camera_range_y1() const;
         float get_camera_range_x2() const;
         float get_camera_range_y2() const;
         float get_camera_max_velocity() const;
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void initialize();
         void fit_camera_range_to_first_page_dimensions();
         void reset();
         void reset_document_camera();
         void reset_document_camera_range();
         void on_switch_out();
         void step_zoom_in();
         void step_zoom_out();
         void set_camera_moving_up();
         void set_camera_moving_down();
         void unset_camera_moving_vertical();
         void set_camera_moving_left();
         void set_camera_moving_right();
         void unset_camera_moving_horizontal();
         void unset_camera_moving();
         void set_map(AllegroFlare::WorldMaps::Maps::Basic* map=nullptr);
         void go_to_origin_or_primary_point_of_interest();
         bool infer_no_pages_are_present();
         void update();
         void render();
         void render_zoom_scale();
         void draw_empty_state(AllegroFlare::FontBin* font_bin=nullptr, std::string placeholder_text="Empty");
         float calc_zoom_position_relative_min_max();
      };
   }
}



