

#include <AllegroFlare/Elements/WorldMapViewer.hpp>

#include <AllegroFlare/Random.hpp>
#include <AllegroFlare/Useful.hpp>
#include <AllegroFlare/WorldMapRenderers/Basic.hpp>
#include <AllegroFlare/WorldMaps/Locations/Basic.hpp>
#include <AllegroFlare/WorldMaps/Locations/Player.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <cmath>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


WorldMapViewer::WorldMapViewer(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , map_view_place()
   , map(nullptr)
   , map_placement()
   , current_page_index_num(0)
   , document_camera()
   , cursor({})
   , target_cursor({})
   , cursor_size(40.0f)
   , cursor_edge_padding(10.0f)
   , cursor_velocity_magnitude_axis_x(0)
   , cursor_velocity_magnitude_axis_y(0)
   , cursor_max_velocity(6.5)
   , document_camera_target_zoom(0)
   , document_camera_zoom_levels({ 0.5f })
   , document_camera_zoom_level_cursor(0)
   , wrap_zoom(false)
   , camera_velocity_magnitude_axis_x(0)
   , camera_velocity_magnitude_axis_y(0)
   , camera_range_x1(DEFAULT_CAMERA_RANGE_X1)
   , camera_range_y1(DEFAULT_CAMERA_RANGE_Y1)
   , camera_range_x2(DEFAULT_CAMERA_RANGE_X2)
   , camera_range_y2(DEFAULT_CAMERA_RANGE_Y2)
   , camera_max_velocity(6.5)
   , state(STATE_UNDEF)
   , state_is_busy(false)
   , state_changed_at(0.0f)
   , initialized(false)
{
}


WorldMapViewer::~WorldMapViewer()
{
}


void WorldMapViewer::set_map_view_place(AllegroFlare::Placement2D map_view_place)
{
   this->map_view_place = map_view_place;
}


void WorldMapViewer::set_cursor(AllegroFlare::Vec2D cursor)
{
   this->cursor = cursor;
}


void WorldMapViewer::set_target_cursor(AllegroFlare::Vec2D target_cursor)
{
   this->target_cursor = target_cursor;
}


void WorldMapViewer::set_cursor_size(float cursor_size)
{
   this->cursor_size = cursor_size;
}


void WorldMapViewer::set_cursor_edge_padding(float cursor_edge_padding)
{
   this->cursor_edge_padding = cursor_edge_padding;
}


void WorldMapViewer::set_cursor_velocity_magnitude_axis_x(float cursor_velocity_magnitude_axis_x)
{
   this->cursor_velocity_magnitude_axis_x = cursor_velocity_magnitude_axis_x;
}


void WorldMapViewer::set_cursor_velocity_magnitude_axis_y(float cursor_velocity_magnitude_axis_y)
{
   this->cursor_velocity_magnitude_axis_y = cursor_velocity_magnitude_axis_y;
}


void WorldMapViewer::set_cursor_max_velocity(float cursor_max_velocity)
{
   this->cursor_max_velocity = cursor_max_velocity;
}


void WorldMapViewer::set_wrap_zoom(bool wrap_zoom)
{
   this->wrap_zoom = wrap_zoom;
}


void WorldMapViewer::set_camera_velocity_magnitude_axis_x(float camera_velocity_magnitude_axis_x)
{
   this->camera_velocity_magnitude_axis_x = camera_velocity_magnitude_axis_x;
}


void WorldMapViewer::set_camera_velocity_magnitude_axis_y(float camera_velocity_magnitude_axis_y)
{
   this->camera_velocity_magnitude_axis_y = camera_velocity_magnitude_axis_y;
}


void WorldMapViewer::set_camera_range_x1(float camera_range_x1)
{
   this->camera_range_x1 = camera_range_x1;
}


void WorldMapViewer::set_camera_range_y1(float camera_range_y1)
{
   this->camera_range_y1 = camera_range_y1;
}


void WorldMapViewer::set_camera_range_x2(float camera_range_x2)
{
   this->camera_range_x2 = camera_range_x2;
}


void WorldMapViewer::set_camera_range_y2(float camera_range_y2)
{
   this->camera_range_y2 = camera_range_y2;
}


void WorldMapViewer::set_camera_max_velocity(float camera_max_velocity)
{
   this->camera_max_velocity = camera_max_velocity;
}


AllegroFlare::BitmapBin* WorldMapViewer::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::FontBin* WorldMapViewer::get_font_bin() const
{
   return font_bin;
}


AllegroFlare::Placement2D WorldMapViewer::get_map_view_place() const
{
   return map_view_place;
}


AllegroFlare::WorldMaps::Maps::Basic* WorldMapViewer::get_map() const
{
   return map;
}


AllegroFlare::Placement2D WorldMapViewer::get_map_placement() const
{
   return map_placement;
}


AllegroFlare::Vec2D WorldMapViewer::get_cursor() const
{
   return cursor;
}


AllegroFlare::Vec2D WorldMapViewer::get_target_cursor() const
{
   return target_cursor;
}


float WorldMapViewer::get_cursor_size() const
{
   return cursor_size;
}


float WorldMapViewer::get_cursor_edge_padding() const
{
   return cursor_edge_padding;
}


float WorldMapViewer::get_cursor_velocity_magnitude_axis_x() const
{
   return cursor_velocity_magnitude_axis_x;
}


float WorldMapViewer::get_cursor_velocity_magnitude_axis_y() const
{
   return cursor_velocity_magnitude_axis_y;
}


float WorldMapViewer::get_cursor_max_velocity() const
{
   return cursor_max_velocity;
}


bool WorldMapViewer::get_wrap_zoom() const
{
   return wrap_zoom;
}


float WorldMapViewer::get_camera_velocity_magnitude_axis_x() const
{
   return camera_velocity_magnitude_axis_x;
}


float WorldMapViewer::get_camera_velocity_magnitude_axis_y() const
{
   return camera_velocity_magnitude_axis_y;
}


float WorldMapViewer::get_camera_range_x1() const
{
   return camera_range_x1;
}


float WorldMapViewer::get_camera_range_y1() const
{
   return camera_range_y1;
}


float WorldMapViewer::get_camera_range_x2() const
{
   return camera_range_x2;
}


float WorldMapViewer::get_camera_range_y2() const
{
   return camera_range_y2;
}


float WorldMapViewer::get_camera_max_velocity() const
{
   return camera_max_velocity;
}


uint32_t WorldMapViewer::get_state() const
{
   return state;
}


void WorldMapViewer::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::set_bitmap_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::set_bitmap_bin]: error: guard \"(!initialized)\" not met");
   }
   this->bitmap_bin = bitmap_bin;
   return;
}

void WorldMapViewer::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::set_font_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::set_font_bin]: error: guard \"(!initialized)\" not met");
   }
   this->font_bin = font_bin;
   return;
}

void WorldMapViewer::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::initialize]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::initialize]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::initialize]: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::initialize]: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::initialize]: error: guard \"font_bin\" not met");
   }
   // set the "name" property (as expected by the Panes::Base class)
   // HERE: Base::set_name("Crime Summary");

   //int margin_x = 0;
   //int margin_y = 0;

   int margin_x = 100;
   int margin_y = 142;
   map_view_place = AllegroFlare::Placement2D(1920/2, 1080/2, 1920-margin_x*2, 1080-margin_y*2);

   //fit_and_position_map();
   //reset_document_camera();
   reset();

   initialized = true;
   return;
}

void WorldMapViewer::fit_and_position_map()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::fit_and_position_map]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::fit_and_position_map]: error: guard \"bitmap_bin\" not met");
   }
   if (!map) return;

   ALLEGRO_BITMAP *map_image = bitmap_bin->auto_get(map->get_background_image_identifier());
   map_placement.size = AllegroFlare::Vec2D{ 0.0f, 0.0f };

   if (map_image)
   {
      map_placement.size = AllegroFlare::Vec2D{ (float)al_get_bitmap_width(map_image), (float)al_get_bitmap_height(map_image) };
   }

   map_placement.position.x = 0; //map_view_place.size.x * 0.5;
   map_placement.position.y = 0; //map_view_place.size.y * 0.5;
   map_placement.align.x = 0.5;
   map_placement.align.y = 0.5;
   //map_placement.rotation = 0;

   return;
}

void WorldMapViewer::fit_camera_range_to_map_dimensions()
{
   if (!map)
   {
      reset_document_camera_range_to_defaults();
   }
   else
   {
      //CatDetective::Chronicle::Panes::CrimeSummaryPage &first_page = pages[0];
      AllegroFlare::Placement2D &first_page_placement = map_placement; //first_page.get_place_ref();

      float h_width = first_page_placement.size.x * 0.5;
      float h_height = first_page_placement.size.y * 0.5;
      camera_range_x1 = -h_width;
      camera_range_y1 = -h_height;
      camera_range_x2 = h_width;
      camera_range_y2 = h_height;
   }

   return;
}

void WorldMapViewer::reset()
{
   // TODO: Confirm these are in the correct order
   fit_and_position_map();
   reset_document_camera();
   unset_cursor_moving(); // TODO: Check if this is redundant
   fit_camera_range_to_map_dimensions();
   snap_cursor_to_origin_or_primary_point_of_interest();
   set_state(STATE_PLAYER_CONTROLLING);
   return;
}

void WorldMapViewer::reset_document_camera()
{
   // TODO: Enable setting these values, ensure they are sorted, and level_cursor is good
   document_camera_zoom_levels = { 1.5, 1.75, 2.1, 2.5 };
   document_camera_zoom_level_cursor = 2; // TODO: Prevent this from being a value outside zoom levels
   camera_velocity_magnitude_axis_x = 0;
   camera_velocity_magnitude_axis_y = 0;

   document_camera.size = AllegroFlare::Vec2D{ map_view_place.size.x, map_view_place.size.y };
   document_camera.position = AllegroFlare::Vec2D{ map_view_place.size.x * 0.5f, map_view_place.size.y * 0.5f };
   document_camera_target_zoom = document_camera_zoom_levels[document_camera_zoom_level_cursor];
   document_camera.set_zoom({document_camera_target_zoom, document_camera_target_zoom});
   return;
}

void WorldMapViewer::reset_document_camera_range_to_defaults()
{
   camera_range_x1 = DEFAULT_CAMERA_RANGE_X1;
   camera_range_y1 = DEFAULT_CAMERA_RANGE_Y1;
   camera_range_x2 = DEFAULT_CAMERA_RANGE_X2;
   camera_range_y2 = DEFAULT_CAMERA_RANGE_Y2;
   return;
}

void WorldMapViewer::on_switch_in()
{
   reset(); // TODO: Consider if this is a good approach, if it should hold the last position, last zoom, always
            // return to primary point of interest, etc.
   return;
}

void WorldMapViewer::on_switch_out()
{
   unset_camera_moving();
   unset_cursor_moving();
   return;
}

bool WorldMapViewer::cursor_control_is_user()
{
   return is_state(STATE_PLAYER_CONTROLLING);
}

void WorldMapViewer::step_zoom_in()
{
   if (!cursor_control_is_user()) return;
   if (document_camera_zoom_levels.empty()) return;
   document_camera_zoom_level_cursor++;
   if (wrap_zoom)
   {
      document_camera_zoom_level_cursor = document_camera_zoom_level_cursor % document_camera_zoom_levels.size();
   }
   else
   {
      if (document_camera_zoom_level_cursor >= document_camera_zoom_levels.size())
         document_camera_zoom_level_cursor = document_camera_zoom_levels.size()-1;
   }
   document_camera_target_zoom = document_camera_zoom_levels[document_camera_zoom_level_cursor];
   return;
}

void WorldMapViewer::step_zoom_out()
{
   if (!cursor_control_is_user()) return;
   if (document_camera_zoom_levels.empty()) return;
   document_camera_zoom_level_cursor--;
   if (wrap_zoom)
   {
      document_camera_zoom_level_cursor += document_camera_zoom_levels.size();
      document_camera_zoom_level_cursor = document_camera_zoom_level_cursor % document_camera_zoom_levels.size();
   }
   else
   {
      if (document_camera_zoom_level_cursor < 0) document_camera_zoom_level_cursor = 0;
   }
   document_camera_target_zoom = document_camera_zoom_levels[document_camera_zoom_level_cursor];
   return;
}

void WorldMapViewer::set_camera_moving_up()
{
   if (!cursor_control_is_user()) return;
   camera_velocity_magnitude_axis_y = -camera_max_velocity;
   return;
}

void WorldMapViewer::set_camera_moving_down()
{
   if (!cursor_control_is_user()) return;
   camera_velocity_magnitude_axis_y = camera_max_velocity;
   return;
}

void WorldMapViewer::unset_camera_moving_vertical()
{
   if (!cursor_control_is_user()) return;
   camera_velocity_magnitude_axis_y = 0.0f;
   return;
}

void WorldMapViewer::set_camera_moving_left()
{
   if (!cursor_control_is_user()) return;
   camera_velocity_magnitude_axis_x = -camera_max_velocity;
   return;
}

void WorldMapViewer::set_camera_moving_right()
{
   if (!cursor_control_is_user()) return;
   camera_velocity_magnitude_axis_x = camera_max_velocity;
   return;
}

void WorldMapViewer::unset_camera_moving_horizontal()
{
   if (!cursor_control_is_user()) return;
   camera_velocity_magnitude_axis_x = 0.0f;
   return;
}

void WorldMapViewer::unset_camera_moving()
{
   unset_camera_moving_vertical();
   unset_camera_moving_horizontal();
}

void WorldMapViewer::set_cursor_moving_up()
{
   if (!cursor_control_is_user()) return;
   cursor_velocity_magnitude_axis_y = -cursor_max_velocity;
   return;
}

void WorldMapViewer::set_cursor_moving_down()
{
   if (!cursor_control_is_user()) return;
   cursor_velocity_magnitude_axis_y = cursor_max_velocity;
   return;
}

void WorldMapViewer::unset_cursor_moving_vertical()
{
   if (!cursor_control_is_user()) return;
   cursor_velocity_magnitude_axis_y = 0.0f;
   return;
}

void WorldMapViewer::set_cursor_moving_left()
{
   if (!cursor_control_is_user()) return;
   cursor_velocity_magnitude_axis_x = -cursor_max_velocity;
   return;
}

void WorldMapViewer::set_cursor_moving_right()
{
   if (!cursor_control_is_user()) return;
   cursor_velocity_magnitude_axis_x = cursor_max_velocity;
   return;
}

void WorldMapViewer::unset_cursor_moving_horizontal()
{
   if (!cursor_control_is_user()) return;
   cursor_velocity_magnitude_axis_x = 0.0f;
   return;
}

void WorldMapViewer::unset_cursor_moving()
{
   unset_cursor_moving_vertical();
   unset_cursor_moving_horizontal();
}

void WorldMapViewer::set_map(AllegroFlare::WorldMaps::Maps::Basic* map)
{
   this->map = map;
   reset();
   //fit_and_position_map();
   //reset_document_camera();
   return;
}

void WorldMapViewer::snap_cursor_to_origin_or_primary_point_of_interest()
{
   float destination_x = 0;
   float destination_y = 0;

   if (map)
   {
      // TODO: Test this case
      std::tie(destination_x, destination_y) = map->infer_primary_point_of_interest_coordinates();
   }
   else
   {
      // TODO: Test this case
      destination_x = map_view_place.size.x * 0.5f;
      destination_y = map_view_place.size.y * 0.5f;
   }

   snap_cursor_to_coordinate(destination_x, destination_y);

   return;
}

void WorldMapViewer::snap_cursor_to_coordinate(float x, float y)
{
   unset_cursor_moving();
   cursor.x = x;
   cursor.y = y;
   set_state(STATE_PLAYER_CONTROLLING);
   return;
}

void WorldMapViewer::move_cursor_to_coordinate(float x, float y)
{
   unset_cursor_moving();
   target_cursor.x = x;
   target_cursor.y = y;
   set_state(STATE_REPOSITIONING_CURSOR);
   return;
}

void WorldMapViewer::move_cursor_to_location(std::string location_id)
{
   if (map)
   {
      // TODO: Test this case
      if (!map->location_exists(location_id))
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Elements::WorldMapViewer::move_cursor_to_location",
            "Could not find the location with identifier \"" + location_id + "\""
         );
      }
      else
      {
         bool found;
         std::pair<float, float> coordinates;
         std::tie(found, coordinates) = map->infer_location_coordinates(location_id);

         if (!found)
         {
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::Elements::WorldMapViewer::move_cursor_to_location",
               "Location with identifier \"" + location_id + "\" exists, but coordinates could not be retrieved."
            );
         }
         else
         {
            move_cursor_to_coordinate(coordinates.first, coordinates.second);
         }
      }
   }
   else
   {
      // TODO: Test this case
      // TODO: Output warning
   }
   return;
}

void WorldMapViewer::render_map()
{
   if (!(al_get_current_display()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::render_map]: error: guard \"al_get_current_display()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::render_map]: error: guard \"al_get_current_display()\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::render_map]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::render_map]: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::render_map]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::render_map]: error: guard \"font_bin\" not met");
   }
   if (infer_no_pages_are_present())
   {
      // draw some placeholder text when there are no pages
      draw_empty_state(font_bin, "No Crime Summary Report");
      return;
   }

   // TODO: add extra scroll offset so clipping travels along with external camera movement
   int clip_x, clip_y, clip_w, clip_h;
   clip_x = (map_view_place.position.x - map_view_place.size.x * map_view_place.align.x);
   clip_y = (map_view_place.position.y - map_view_place.size.y * map_view_place.align.y);
   clip_w = map_view_place.size.x;
   clip_h = map_view_place.size.y;

   // Scale the clipping points to match the actual resolution of the display, rather than the 
   // surface virtual resolution which is 1920x1080.
   // NOTE: The technique for retrieving physical surface dimentions here feels a bit sloppy because it's
   // requesting hardware state/data (which is not the purview of this component) from deep within this
   // omponent which feels out of scope, but, it's probably fine tbh because I think this information is
   // already actively stored in the allegro state.

   ALLEGRO_DISPLAY *current_display = al_get_current_display();
   int physical_surface_width = al_get_display_width(current_display);
   int physical_surface_height = al_get_display_height(current_display);
   int virtual_surface_width = 1920;
   int virtual_surface_height = 1080;

   if (virtual_surface_width == physical_surface_width && virtual_surface_height == physical_surface_height)
   {
      // do no scaling, the physical and virtual dimensions are identical
   }
   else
   {
      float x_scale_change = physical_surface_width / (float)virtual_surface_width;
      float y_scale_change = physical_surface_height / (float)virtual_surface_height;
      clip_x *= x_scale_change;
      clip_y *= y_scale_change;
      clip_w *= x_scale_change;
      clip_h *= y_scale_change;
   }

   al_set_clipping_rectangle(clip_x, clip_y, clip_w, clip_h);
   document_camera.start_reverse_transform();

   // render pages in reverse order from back to front
   /* // HERE
   for (int i=(pages.size()-1); i>=0; i--)
   {
      HERE: pages[i].render(bitmap_bin);
   }
   */

   // NEW:
   AllegroFlare::WorldMapRenderers::Basic renderer(bitmap_bin, font_bin, map);
   renderer.render();

   // Draw the cursor
   // TODO: Project this into the map
   //al_draw_circle(cursor.x, cursor.y, 13, ALLEGRO_COLOR{0, 0, 1, 1}, 2.0f); // debuggin

   document_camera.restore_transform();

   AllegroFlare::Vec2D transformed_cursor = cursor;
   document_camera.transform_coordinates(&transformed_cursor.x, &transformed_cursor.y);
   draw_cursor(transformed_cursor.x, transformed_cursor.y);


   al_reset_clipping_rectangle(); // TODO: revert to previous clipping instead


   return;
}

void WorldMapViewer::draw_cursor(float x, float y)
{
   //float size = cursor_size;
   float hsize = cursor_size * 0.5f;
   float thickness = 6.0;
   // Draw shadow
   al_draw_rectangle(x-hsize, y-hsize, x+hsize, y+hsize, ALLEGRO_COLOR{0.0, 0.0, 0.0, 0.4}, 6.0 + 6.0);
   // Draw shape
   al_draw_rectangle(x-hsize, y-hsize, x+hsize, y+hsize, ALLEGRO_COLOR{0.95, 0.74, 0.5, 1.0}, 6.0);
   return;
}

bool WorldMapViewer::infer_no_pages_are_present()
{
   return map == nullptr;
   //return pages.empty();
}

void WorldMapViewer::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::update]: error: guard \"initialized\" not met");
   }
   update_state();
   // NOTE: Order of transformations is important, for example, velocity is relative to zoom

   // Update camera zoom
   float f_zoom = document_camera.get_zoom().x;
   float next_zoom = (document_camera_target_zoom - f_zoom) * 0.175 + f_zoom;
   document_camera.set_zoom({next_zoom, next_zoom});

   // update cursor position by the velocity
   AllegroFlare::Vec2D document_camera_zoom = document_camera.get_zoom();
   cursor.x += (cursor_velocity_magnitude_axis_x / document_camera_zoom.x);
   cursor.y += (cursor_velocity_magnitude_axis_y / document_camera_zoom.y);

   // ensure the cursor does not extend beyond the constraints
   // TODO: Avoid using the "camera_range_x1"/"camera_range_x2" and find a better way to manage cursor ranges instead
   //cursor.x -= map_view_place.size.x * 0.5;
   //cursor.x =
      //AllegroFlare::clamp<float>(camera_range_x1, camera_range_x2, cursor.x)
      //+ map_view_place.size.x * 0.5;

   //cursor.y -= map_view_place.size.y * 0.5;
   //cursor.y =
      //AllegroFlare::clamp<float>(camera_range_y1, camera_range_y2, cursor.y)
      //+ map_view_place.size.y * 0.5;
   float padding = cursor_size * 0.5 + cursor_edge_padding; // 30;
   cursor.x = AllegroFlare::clamp<float>(0 + padding, 1920 - padding, cursor.x);
   cursor.y = AllegroFlare::clamp<float>(0 + padding, 1080 - padding, cursor.y);

   // Update camera position by the velocity
   document_camera.position.x += camera_velocity_magnitude_axis_x;
   document_camera.position.y += camera_velocity_magnitude_axis_y;

   // Have the camera follow the cursor, and/or block its range
   bool camera_follows_cursor = true;
   if (camera_follows_cursor)
   {
      document_camera.position.x = cursor.x;
      document_camera.position.y = cursor.y;

      float top, right, bottom, left;
      std::tie(top, right, bottom, left) = document_camera.get_outermost_coordinates_trbl();

      if (left < 0) { float dist = -left; document_camera.position.x += dist; }
      if (top < 0) { float dist = -top; document_camera.position.y += dist; }
      if (bottom > 1080) { float dist = bottom - 1080; document_camera.position.y -= dist; }
      if (right > 1920) { float dist = right - 1920; document_camera.position.x -= dist; }
      //if (outermost_coor
   }
   else
   {
      // ensure the camera does not extand beyond the constraints
      document_camera.position.x -= map_view_place.size.x * 0.5;
      document_camera.position.x =
         AllegroFlare::clamp<float>(camera_range_x1, camera_range_x2, document_camera.position.x)
         + map_view_place.size.x * 0.5;
      document_camera.position.y -= map_view_place.size.y * 0.5;
      document_camera.position.y =
         AllegroFlare::clamp<float>(camera_range_y1, camera_range_y2, document_camera.position.y)
         + map_view_place.size.y * 0.5;
   }

   return;
}

void WorldMapViewer::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::render]: error: guard \"initialized\" not met");
   }
   if (infer_no_pages_are_present())
   {
      //draw_empty_state(font_bin, "No Crime Summary Report");
      draw_empty_state(font_bin, "No Map");
   }
   else
   {
      map_view_place.start_transform();

      // draw an arbitrary frame
      al_draw_rectangle(0, 0, map_view_place.size.x, map_view_place.size.y, ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2}, 2.0f);
      // render the elements
      render_map();
      render_page_numbers();
      render_zoom_scale();
      render_coordinates();

      map_view_place.restore_transform();
   }

   return;
}

std::pair<bool, std::string> WorldMapViewer::infer_focused_location_label()
{
   if (!(map))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::infer_focused_location_label]: error: guard \"map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::infer_focused_location_label]: error: guard \"map\" not met");
   }
   std::string location_id = map->location_id_at(cursor.x, cursor.y);
   if (location_id.empty()) return { false, "" };

   AllegroFlare::WorldMaps::Locations::Base *found_location = map->find_location_by_id(location_id);

   std::string result;
   if (!found_location)
   {
      AllegroFlare::Logger::warn_from_once(
         "AllegroFlare::Elements::WorldMapViewer",
         "Could not find a location for the location_id \"" + location_id + "\""
      );
      //result = location_id;
      return { false, location_id };
   }
   else
   {
      if (found_location->is_type(AllegroFlare::WorldMaps::Locations::Basic::TYPE))
      {
         AllegroFlare::WorldMaps::Locations::Basic *as =
            static_cast<AllegroFlare::WorldMaps::Locations::Basic*>(found_location);
         result = as->get_label();
      }
      else if (found_location->is_type(AllegroFlare::WorldMaps::Locations::Player::TYPE))
      {
         return { true, "current location" };
      }
      else
      {
         AllegroFlare::Logger::warn_from_once(
            "AllegroFlare::Elements::WorldMapViewer",
            "Could not infer a label for the location of type \"" + found_location->get_type() + "\""
         );
         //result = location_id;
         return { false, location_id };
      }
   }
   return { true, result };
}

void WorldMapViewer::render_page_numbers()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::render_page_numbers]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::render_page_numbers]: error: guard \"initialized\" not met");
   }
   bool currently_over_location;
   std::string focused_location_label;
   std::tie(currently_over_location, focused_location_label) = infer_focused_location_label();

   if (!currently_over_location) focused_location_label = " - no location - ";
     //default_argument: '"- no location -"'

   if (!currently_over_location) return;


   float x = map_view_place.size.x * 0.5;
   float y = map_view_place.size.y;

   ALLEGRO_FONT *font = obtain_font();
   float text_width = al_get_text_width(font, focused_location_label.c_str());
   float text_height = al_get_font_line_height(font);
   float h_text_width = text_width/2;
   float h_text_height = text_height/2;
   AllegroFlare::Vec2D padding{30, 20};
   float o = 0.8;
   ALLEGRO_COLOR text_color = currently_over_location
                            ? ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0}
                            : ALLEGRO_COLOR{0.28f*o, 0.32f*o, 0.41f*o, 1.0f*o}
                            ;

   al_draw_filled_rounded_rectangle(
      x-h_text_width - padding.x,
      y-h_text_height - padding.y,
      x+h_text_width + padding.x,
      y+h_text_height + padding.y,
      8.0f,
      8.0f,
      ALLEGRO_COLOR{0, 0, 0, 0.5}
   );
   al_draw_text(
      font,
      text_color,
      x,
      y-h_text_height,
      ALLEGRO_ALIGN_CENTER,
      focused_location_label.c_str()
   );
   return;
}

void WorldMapViewer::render_coordinates()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::render_coordinates]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::render_coordinates]: error: guard \"initialized\" not met");
   }
   //bool currently_over_location;
   std::stringstream coordinates;
   bool render_coordinates_as_int = true;
   if (render_coordinates_as_int) coordinates << (int)cursor.x << ", " << (int)cursor.y;
   else coordinates << cursor.x << ", " << cursor.y;
   std::string text_to_render = coordinates.str();
   //std::tie(currently_over_location, focused_location_label) = infer_focused_location_label();

   //if (!currently_over_location) focused_location_label = " - no location - ";
     //default_argument: '"- no location -"'


   float x = map_view_place.size.x - 100;
   float y = map_view_place.size.y - 60;

   ALLEGRO_FONT *font = obtain_small_ui_font();
   float text_width = al_get_text_width(font, text_to_render.c_str());
   float text_height = al_get_font_line_height(font);
   float h_text_width = text_width/2;
   float h_text_height = text_height/2;
   AllegroFlare::Vec2D padding{30, 20};
   float o = 0.8;
   //ALLEGRO_COLOR text_color = currently_over_location
                            //? ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0}
                            //: ALLEGRO_COLOR{0.28f*o, 0.32f*o, 0.41f*o, 1.0f*o}
                            //;
   ALLEGRO_COLOR text_color = ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0};

   //al_draw_filled_rounded_rectangle(
      //x-h_text_width - padding.x,
      //y-h_text_height - padding.y,
      //x+h_text_width + padding.x,
      //y+h_text_height + padding.y,
      //8.0f,
      //8.0f,
      //ALLEGRO_COLOR{0, 0, 0, 0.5}
   //);
   al_draw_text(
      font,
      text_color,
      x,
      y-h_text_height,
      ALLEGRO_ALIGN_RIGHT,
      text_to_render.c_str()
   );
   return;
}

void WorldMapViewer::render_zoom_scale()
{
   float height = 380;
   float x_pos = map_view_place.size.x;
   float y_pos = map_view_place.size.y * 0.5 - height / 2;
   float zoom_cursor_pos = 1.0 - calc_zoom_position_relative_min_max();
   float padding_x = 32;
   float padding_y = 48;
   float roundness = padding_x;

   // draw background rectangle, same as "render_page_numbers"
   al_draw_filled_rounded_rectangle(
      x_pos - padding_x,
      y_pos - padding_y,
      x_pos + padding_x,
      y_pos + padding_y + height,
      roundness,
      roundness,
      ALLEGRO_COLOR{0, 0, 0, 0.5}
   );

   // draw the meter
   al_draw_line(x_pos, y_pos, x_pos, y_pos+height, ALLEGRO_COLOR{1,1,1,1}, 4.0);

   // draw the head on the bar
   al_draw_filled_circle(x_pos, y_pos + height * zoom_cursor_pos, 12, ALLEGRO_COLOR{1, 1, 1, 1});

   // draw the "zoom" label
   // TODO
   return;
}

void WorldMapViewer::draw_empty_state(AllegroFlare::FontBin* font_bin, std::string placeholder_text)
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::draw_empty_state]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::draw_empty_state]: error: guard \"font_bin\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::draw_empty_state]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::draw_empty_state]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   static constexpr float frame_width = 1920;
   static constexpr float frame_height = 1080;
   static constexpr float width = frame_width - 100 * 2;
   static constexpr float height = frame_height - 142 * 2;
   static constexpr float cx = frame_width / 2;
   static constexpr float cy = frame_height / 2;

   static constexpr float x1 = cx - width * 0.5;;
   static constexpr float y1 = cy - height * 0.5;
   static constexpr float x2 = cx + width * 0.5;
   static constexpr float y2 = cy + height * 0.5;

   al_draw_rectangle(x1, y1, x2, y2, ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2}, 2.0f);

   // draw the text
   static const std::string FONT_IDENTIFIER = "Inter-Medium.ttf -36";
   ALLEGRO_FONT* font = font_bin->operator[](FONT_IDENTIFIER);

   al_draw_text(
         font,
         ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2},
         1920 * 0.5,
         1080 * 0.5,
         ALLEGRO_ALIGN_CENTER,
         placeholder_text.c_str()
      );

   return;
}

float WorldMapViewer::calc_zoom_position_relative_min_max()
{
   if (document_camera_zoom_levels.empty()) return 0.0f;
   auto [min, max] = std::minmax_element(begin(document_camera_zoom_levels), end(document_camera_zoom_levels));
   float range = *max - *min;
   return (document_camera.get_zoom().x - *min) / (range);
}

void WorldMapViewer::set_state(uint32_t state, bool override_if_busy)
{
   if (!(is_valid_state(state)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::set_state]: error: guard \"is_valid_state(state)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::set_state]: error: guard \"is_valid_state(state)\" not met");
   }
   if (this->state == state) return;
   if (!override_if_busy && state_is_busy) return;
   uint32_t previous_state = this->state;

   switch (state)
   {
      case STATE_PLAYER_CONTROLLING:
      break;

      case STATE_REPOSITIONING_CURSOR:
      break;

      default:
         throw std::runtime_error("weird error");
      break;
   }

   this->state = state;
   state_changed_at = al_get_time();

   return;
}

void WorldMapViewer::update_state(float time_now)
{
   if (!(is_valid_state(state)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::update_state]: error: guard \"is_valid_state(state)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::update_state]: error: guard \"is_valid_state(state)\" not met");
   }
   float age = infer_current_state_age(time_now);

   switch (state)
   {
      case STATE_PLAYER_CONTROLLING: {
      } break;

      case STATE_REPOSITIONING_CURSOR: {
         float reposition_speed = 0.07f;
         float min_dist_to_end = 1.0f;

         cursor.x = (target_cursor.x - cursor.x) * reposition_speed + cursor.x;
         cursor.y = (target_cursor.y - cursor.y) * reposition_speed + cursor.y;

         float x_dist = std::abs(target_cursor.x - cursor.x); // Maybe to a magnitude/velocity calculation instead?
         float y_dist = std::abs(target_cursor.y - cursor.y);
         if (x_dist <= min_dist_to_end && y_dist <= min_dist_to_end)
         {
            cursor.x = target_cursor.x;
            cursor.y = target_cursor.y;
            set_state(STATE_PLAYER_CONTROLLING);
         }

      } break;

      default: {
         throw std::runtime_error("weird error");
      } break;
   }

   return;
}

bool WorldMapViewer::is_valid_state(uint32_t state)
{
   std::set<uint32_t> valid_states =
   {
      STATE_PLAYER_CONTROLLING,
      STATE_REPOSITIONING_CURSOR,
   };
   return (valid_states.count(state) > 0);
}

bool WorldMapViewer::is_state(uint32_t possible_state)
{
   return (state == possible_state);
}

float WorldMapViewer::infer_current_state_age(float time_now)
{
   return (time_now - state_changed_at);
}

ALLEGRO_FONT* WorldMapViewer::obtain_font()
{
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::obtain_font]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::obtain_font]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::obtain_font]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::obtain_font]: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::obtain_font]: error: guard \"font_bin\" not met");
   }
   static const std::string FONT_IDENTIFIER = "Inter-Medium.ttf -36";
   ALLEGRO_FONT* result_font = font_bin->operator[](FONT_IDENTIFIER);
   return result_font;
}

ALLEGRO_FONT* WorldMapViewer::obtain_small_ui_font()
{
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::obtain_small_ui_font]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::obtain_small_ui_font]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::obtain_small_ui_font]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::obtain_small_ui_font]: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::WorldMapViewer::obtain_small_ui_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::WorldMapViewer::obtain_small_ui_font]: error: guard \"font_bin\" not met");
   }
   static const std::string FONT_IDENTIFIER = "Inter-Regular.ttf -28";
   ALLEGRO_FONT* result_font = font_bin->operator[](FONT_IDENTIFIER);
   return result_font;
}


} // namespace Elements
} // namespace AllegroFlare


