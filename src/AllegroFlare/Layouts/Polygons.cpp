

#include <AllegroFlare/Layouts/Polygons.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Layouts/ElementFactory.hpp>
#include <AllegroFlare/Logger.hpp>
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


Polygons::Polygons(std::string tmj_filename)
   : tmj_filename(tmj_filename)
   , layout_width(0.0f)
   , layout_height(0.0f)
   , polygons({})
   , initialized(false)
{
}


Polygons::~Polygons()
{
}


void Polygons::set_tmj_filename(std::string tmj_filename)
{
   if (get_initialized()) throw std::runtime_error("[Polygons::set_tmj_filename]: error: guard \"get_initialized()\" not met.");
   this->tmj_filename = tmj_filename;
}


bool Polygons::get_initialized() const
{
   return initialized;
}


float Polygons::get_layout_width()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::Polygons::get_layout_width]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::Polygons::get_layout_width]: error: guard \"initialized\" not met");
   }
   return layout_width;
}

float Polygons::get_layout_height()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::Polygons::get_layout_height]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::Polygons::get_layout_height]: error: guard \"initialized\" not met");
   }
   return layout_height;
}

void Polygons::set_polygons_behavior(std::map<std::string, std::tuple<std::function<void()>, std::function<void()>, std::function<void()>>> behavior_map)
{
   // TODO: this method
   return;
}

void Polygons::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::Polygons::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::Polygons::initialize]: error: guard \"(!initialized)\" not met");
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
      if (!object->polygon.empty() && object->type != "shape")
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Layouts::Polygons::initialize",
            "When loading object (tmj_object_id \"" + std::to_string(object->id) + "\"), the object contains "
               "polygon points, but it is not of the type \"shape\". For this implementation, a shape type (that "
               "has the expected custom properties for \"shape\") is expected to be present for polygons."
         );
      }
      else if (object->type == "shape")
      {
         polygons[object->id] = AllegroFlare::Layouts::ElementFactory::build_polygon_from_tmj_object(object);
      }
   });

   // TODO: Validate targets

   initialized = true;
}

AllegroFlare::Layouts::Elements::Polygon* Polygons::find_polygon_by_tmj_object_id(int tmj_object_id)
{
   // TODO: Test this
   auto it = polygons.find(tmj_object_id);
   if (it == polygons.end()) return nullptr;
   return &it->second;
}

AllegroFlare::Layouts::Elements::Polygon* Polygons::find_polygon_by_name(std::string name)
{
   // TODO: Test this
   for (auto &polygon : polygons)
   {
      if (polygon.second.name == name) return &polygon.second;
   }
   return nullptr;
}

int Polygons::extract_int_or_default(AllegroFlare::Tiled::TMJObject* object, std::string key, int default_fallback)
{
   AllegroFlare::Tiled::TMJObjectCustomProperties &custom_properties = object->custom_properties;

   // TODO: Add warning when present but not an int
   if (!(custom_properties.exists(key) && custom_properties.is_int(key))) return default_fallback;
   return custom_properties.get_int(key);
}

int Polygons::extract_int_or_throw(AllegroFlare::Tiled::TMJObject* object, std::string key)
{
   AllegroFlare::Tiled::TMJObjectCustomProperties &custom_properties = object->custom_properties;

   if (!(custom_properties.exists(key) && custom_properties.is_int(key)))
   {
      // Doesn't exist
      AllegroFlare::Logger::throw_error(
         "Layouts::CursorMaps::CursorMap::extract_int_or_throw",
         "Expecting the custom property \"" + key + "\" on object name \"" + object->name + "\" (tmj_object_id \""
            + std::to_string(object->id) + "\") but it does not exist."
      );
   }
   return custom_properties.get_int(key);
      AllegroFlare::Logger::throw_error(
         "Layouts::CursorMaps::CursorMap::extract_int_or_throw",
         "Expecting the custom property \"" + key + "\" on object name \"" + object->name + "\" (tmj_object_id \""
            + std::to_string(object->id) + "\") but it does not exist."
      );
}

std::string Polygons::extract_color_hex_or_default(AllegroFlare::Tiled::TMJObject* object, std::string key, std::string default_fallback)
{
   AllegroFlare::Tiled::TMJObjectCustomProperties &custom_properties = object->custom_properties;

   // TODO: Add warning when present but not an int
   if (!(custom_properties.exists(key) && custom_properties.is_color(key))) return default_fallback;
   return custom_properties.get_color(key);
}

void Polygons::render()
{
   for (auto &polygon_ : polygons)
   {
      AllegroFlare::Layouts::Elements::Polygon &polygon = polygon_.second;
      //ALLEGRO_COLOR polygon_fill_color = al_color_name("purple");
      polygon.path.draw_shape(polygon.fill_color);
      //polygon.path.draw_shape(polygon_fill_color);
   }
   return;
}

void Polygons::render_debug(float line_thickness)
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::Polygons::render_debug]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::Polygons::render_debug]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   ALLEGRO_COLOR canvas_frame_color = al_color_name("purple");
   AllegroFlare::Color color_a = al_color_name("cyan");
   AllegroFlare::Color color_b = al_color_name("aliceblue");
   AllegroFlare::Color result_color = AllegroFlare::Color().mix(color_a, color_b, 0.5);
   ALLEGRO_COLOR cursor_destination_color = result_color.to_al();
   ALLEGRO_COLOR yellow_color = al_color_name("yellow");

   // Draw the canvas frame
   draw_container_frame(0, 0, layout_width, layout_height, canvas_frame_color, line_thickness);

   // Draw the destinations
   for (auto &polygon_ : polygons)
   {
      AllegroFlare::Layouts::Elements::Polygon &polygon = polygon_.second;
      //::Layouts::CursorMaps::CursorDestination &frame = frame_.second;
      draw_container_frame(
         polygon.x,
         polygon.y,
         polygon.x + polygon.width,
         polygon.y + polygon.height,
         cursor_destination_color,
         line_thickness
      );

      //polygon.path.draw_shape(polygon.x, polygon.y, yellow_color);
      //polygon.path.draw_shape(cursor_);
      //polygon.path.draw_shape(result_color);
      polygon.path.draw_outline(yellow_color, 2.0);
   }

   return;
}

void Polygons::draw_container_frame(float x, float y, float x2, float y2, ALLEGRO_COLOR color, float line_thickness)
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


