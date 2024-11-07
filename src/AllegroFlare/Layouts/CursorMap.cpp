

#include <AllegroFlare/Layouts/CursorMap.hpp>

#include <AllegroFlare/Layouts/ElementFactory.hpp>
#include <AllegroFlare/Tiled/TMJDataLoader.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Layouts
{


CursorMap::CursorMap(std::string tmj_filename)
   : tmj_filename(tmj_filename)
   , layout_width(0.0f)
   , layout_height(0.0f)
   , positions({})
   , initialized(false)
{
}


CursorMap::~CursorMap()
{
}


void CursorMap::set_tmj_filename(std::string tmj_filename)
{
   if (get_initialized()) throw std::runtime_error("[CursorMap::set_tmj_filename]: error: guard \"get_initialized()\" not met.");
   this->tmj_filename = tmj_filename;
}


bool CursorMap::get_initialized() const
{
   return initialized;
}


float CursorMap::get_layout_width()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::CursorMap::get_layout_width]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::CursorMap::get_layout_width]: error: guard \"initialized\" not met");
   }
   return layout_width;
}

float CursorMap::get_layout_height()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::CursorMap::get_layout_height]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::CursorMap::get_layout_height]: error: guard \"initialized\" not met");
   }
   return layout_height;
}

void CursorMap::set_positions_behavior(std::map<std::string, std::tuple<std::function<void()>, std::function<void()>, std::function<void()>>> behavior_map)
{
   // TODO: this method
   return;
}

void CursorMap::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::CursorMap::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::CursorMap::initialize]: error: guard \"(!initialized)\" not met");
   }
   AllegroFlare::Tiled::TMJDataLoader tmj_data_loader(tmj_filename);
   tmj_data_loader.load();

   int num_rows = tmj_data_loader.get_num_rows();
   int num_columns = tmj_data_loader.get_num_columns();
   int tile_width = tmj_data_loader.get_tile_width();
   int tile_height = tmj_data_loader.get_tile_height();
   layout_width = num_columns * tile_width;
   layout_height = num_rows * tile_height;

   tmj_data_loader.for_each_object([this](AllegroFlare::Tiled::TMJObject* object, void *user_data){
      if (object->type == "cursor_destination")
      {
         positions[object->id] =
            AllegroFlare::Layouts::ElementFactory::build_cursor_destination_from_tmj_object(object);
      }
   });

   // TODO: Validate targets

   initialized = true;
}

AllegroFlare::Layouts::Elements::CursorDestination* CursorMap::get_initial_cursor_destination()
{
   if (!((!positions.empty())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::CursorMap::get_initial_cursor_destination]: error: guard \"(!positions.empty())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::CursorMap::get_initial_cursor_destination]: error: guard \"(!positions.empty())\" not met");
   }
   return &positions.begin()->second;
}

AllegroFlare::Layouts::Elements::CursorDestination* CursorMap::find_position_by_tmj_object_id(int tmj_object_id)
{
   // TODO: Test this
   auto it = positions.find(tmj_object_id);
   if (it == positions.end()) return nullptr;
   return &it->second;
}

AllegroFlare::Layouts::Elements::CursorDestination* CursorMap::find_position_by_name(std::string name)
{
   // TODO: Test this
   for (auto &position : positions)
   {
      if (position.second.name == name) return &position.second;
   }
   return nullptr;
}

void CursorMap::render_debug(float line_thickness)
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::CursorMap::render_debug]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::CursorMap::render_debug]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   ALLEGRO_COLOR canvas_frame_color = al_color_name("purple");
   ALLEGRO_COLOR cursor_destination_color = al_color_name("cyan");

   // Draw the canvas frame
   draw_container_frame(0, 0, layout_width, layout_height, canvas_frame_color, line_thickness);

   // Draw the destinations
   for (auto &position_ : positions)
   {
      //Layouts::CursorMaps::CursorDestination &position = position_.second;
      AllegroFlare::Layouts::Elements::CursorDestination &position = position_.second;

      draw_container_frame(
         position.x,
         position.y,
         position.x + position.width,
         position.y + position.height,
         cursor_destination_color,
         line_thickness
      );
   }

   return;
}

void CursorMap::draw_container_frame(float x, float y, float x2, float y2, ALLEGRO_COLOR color, float line_thickness)
{
   float w = x2 - x;
   float h = y2 - y;
   // TODO: Make this into a prim
   al_draw_rectangle(
      x,
      y,
      x + w,
      y + h,
      color,
      line_thickness
   );

   al_draw_line(
      x,
      y,
      x + w,
      y + h,
      color,
      line_thickness
   );

   al_draw_line(
      x + w,
      y,
      x,
      y + h,
      color,
      line_thickness
   );
   return;
}


} // namespace Layouts
} // namespace AllegroFlare


