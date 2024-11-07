

#include <AllegroFlare/Layouts/Frames.hpp>

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


Frames::Frames(std::string tmj_filename)
   : tmj_filename(tmj_filename)
   , layout_width(0.0f)
   , layout_height(0.0f)
   , frames({})
   , initialized(false)
{
}


Frames::~Frames()
{
}


void Frames::set_tmj_filename(std::string tmj_filename)
{
   if (get_initialized()) throw std::runtime_error("[Frames::set_tmj_filename]: error: guard \"get_initialized()\" not met.");
   this->tmj_filename = tmj_filename;
}


bool Frames::get_initialized() const
{
   return initialized;
}


float Frames::get_layout_width()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::Frames::get_layout_width]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::Frames::get_layout_width]: error: guard \"initialized\" not met");
   }
   return layout_width;
}

float Frames::get_layout_height()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::Frames::get_layout_height]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::Frames::get_layout_height]: error: guard \"initialized\" not met");
   }
   return layout_height;
}

void Frames::set_frames_behavior(std::map<std::string, std::tuple<std::function<void()>, std::function<void()>, std::function<void()>>> behavior_map)
{
   // TODO: this method
   return;
}

void Frames::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::Frames::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::Frames::initialize]: error: guard \"(!initialized)\" not met");
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
      if (object->type == "frame")
      {
         frames[object->id] = AllegroFlare::Layouts::ElementFactory::build_frame_from_tmj_object(object);
      }
   });

   // TODO: Validate targets

   initialized = true;
}

AllegroFlare::Layouts::Elements::Frame* Frames::find_frame_by_tmj_object_id(int tmj_object_id)
{
   // TODO: Test this
   auto it = frames.find(tmj_object_id);
   if (it == frames.end()) return nullptr;
   return &it->second;
}

AllegroFlare::Layouts::Elements::Frame* Frames::find_frame_by_name(std::string name)
{
   // TODO: Test this
   for (auto &frame : frames)
   {
      if (frame.second.name == name) return &frame.second;
   }
   return nullptr;
}

int Frames::extract_int_or_default(AllegroFlare::Tiled::TMJObject* object, std::string key, int default_fallback)
{
   AllegroFlare::Tiled::TMJObjectCustomProperties &custom_properties = object->custom_properties;

   // TODO: Add warning when present but not an int
   if (!(custom_properties.exists(key) && custom_properties.is_int(key))) return default_fallback;
   return custom_properties.get_int(key);
}

int Frames::extract_int_or_throw(AllegroFlare::Tiled::TMJObject* object, std::string key)
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
}

void Frames::render_debug(float line_thickness)
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::Frames::render_debug]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::Frames::render_debug]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   ALLEGRO_COLOR canvas_frame_color = al_color_name("purple");
   AllegroFlare::Color color_a = al_color_name("cyan");
   AllegroFlare::Color color_b = al_color_name("aliceblue");
   AllegroFlare::Color result_color = AllegroFlare::Color().mix(color_a, color_b, 0.5);
   ALLEGRO_COLOR cursor_destination_color = result_color.to_al();

   // Draw the canvas frame
   draw_container_frame(0, 0, layout_width, layout_height, canvas_frame_color, line_thickness);

   // Draw the destinations
   for (auto &frame_ : frames)
   {
      AllegroFlare::Layouts::Elements::Frame &frame = frame_.second;
      //::Layouts::CursorMaps::CursorDestination &frame = frame_.second;
      draw_container_frame(
         frame.x,
         frame.y,
         frame.x + frame.width,
         frame.y + frame.height,
         cursor_destination_color,
         line_thickness
      );
   }

   return;
}

void Frames::draw_container_frame(float x, float y, float x2, float y2, ALLEGRO_COLOR color, float line_thickness)
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


