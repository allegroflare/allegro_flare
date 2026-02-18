

#include <AllegroFlare/Layouts/ElementFactory.hpp>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/Tiled/TMJDataLoader.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Layouts
{


ElementFactory::ElementFactory()
{
}


ElementFactory::~ElementFactory()
{
}


AllegroFlare::Layouts::Elements::Polygon ElementFactory::build_polygon_from_tmj_object(AllegroFlare::Tiled::TMJObject* object, bool throw_if_not_counterclockwise)
{
   if (!(object))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::ElementFactory::build_polygon_from_tmj_object]: error: guard \"object\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::ElementFactory::build_polygon_from_tmj_object]: error: guard \"object\" not met");
   }
   AllegroFlare::Layouts::Elements::Polygon result_polygon;

   result_polygon.tmj_object_id = object->id;
   result_polygon.x = object->x;
   result_polygon.y = object->y;
   //result_polygon.width = object->width; // TODO: Calculate width and height
   //result_polygon.height = object->height;

   result_polygon.polygon = object->polygon;


   result_polygon.path.point = result_polygon.polygon;
   result_polygon.path.move(result_polygon.x, result_polygon.y);
   //result_polygon.path.update_vertexs(); // ???
   result_polygon.path.refresh_segment_info();
   result_polygon.width = result_polygon.path.width();
   result_polygon.height = result_polygon.path.height();
   result_polygon.name = object->name;



   if (throw_if_not_counterclockwise)
   {
      // TODO: Test this
      // TODO: Consider moving this to after parsing, so instead of a single error it could present a list of
      // polygons thare are not properly countercolockwise
      bool is_counterclockwise = result_polygon.path.infer_is_counterclockwise();
      if (!is_counterclockwise)
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Layouts::ElementFactory::build_polygon_from_tmj_object",
            "Expecting the polygon object (name \"" + object->name + "\", tmj_object_id \""
               + std::to_string(object->id) + "\") to be counterclockwise, but it is not. For polygons to render "
               "as expected the vertices must be counterclockwise. If you have the \"ReverseVertexOrder\" Tiled "
               "extension installed (The extension is located in this project at "
               "\"scripts/tiled/extensions/ReverseVertexOrder.js\", it provides adds a right-click option the "
               "object menu in tiled with the action \"Reverse vertex order\"."
         );
      }
   }



   AllegroFlare::Vec2D top_left = result_polygon.path.top_left();
   result_polygon.x = top_left.x; //object->x;
   result_polygon.y = top_left.y; //object->y;


   std::string color_string = extract_color_hex_or_default(object, "fill_color", "#ff00aacc");
   std::tuple<float, float, float, float> fill_color_components =
      AllegroFlare::Tiled::TMJDataLoader::convert_hex_to_rgba_f(color_string);
   ALLEGRO_COLOR polygon_fill_color;
   polygon_fill_color.r = std::get<0>(fill_color_components);
   polygon_fill_color.g = std::get<1>(fill_color_components);
   polygon_fill_color.b = std::get<2>(fill_color_components);
   polygon_fill_color.a = 1.0;


   result_polygon.fill_color = polygon_fill_color;


   //color_hex

   //result_position.move_up_to_target_tmj_object_id =
      //extract_int_or_default(object, "move_up_to_target_id");
   //result_position.move_down_to_target_tmj_object_id =
      //extract_int_or_default(object, "move_down_to_target_id");
   //result_position.move_left_to_target_tmj_object_id =
      //extract_int_or_default(object, "move_left_to_target_id");
   //result_position.move_right_to_target_tmj_object_id =
      //extract_int_or_default(object, "move_right_to_target_id");

   return result_polygon;
}

AllegroFlare::Layouts::Elements::Text ElementFactory::build_text_from_tmj_object(AllegroFlare::Tiled::TMJObject* object)
{
   if (!(object))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::ElementFactory::build_text_from_tmj_object]: error: guard \"object\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::ElementFactory::build_text_from_tmj_object]: error: guard \"object\" not met");
   }
   float x = object->x;
   float y = object->y;
   float w = object->width;
   float h = object->height;
   float align_x = translate_alignment_string_to_float(object->text__align_horizontal);
   float align_y = translate_alignment_string_to_float(object->text__align_vertical);
   std::string text = object->text__text;
   int font_size = -object->text__font_size;
   std::string font_family = object->text__font_name;
   ALLEGRO_COLOR color = object->text__color;

   AllegroFlare::Layouts::Elements::Text result_text;

   result_text.x = x;
   result_text.y = y;
   result_text.width = w;
   result_text.height = h;
   result_text.align_x = align_x;
   result_text.align_y = align_y;
   result_text.font_family = font_family;
   result_text.font_size = font_size;
   result_text.color = color;

   return result_text;
}

AllegroFlare::Layouts::Elements::CursorDestination ElementFactory::build_cursor_destination_from_tmj_object(AllegroFlare::Tiled::TMJObject* object)
{
   if (!(object))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::ElementFactory::build_cursor_destination_from_tmj_object]: error: guard \"object\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::ElementFactory::build_cursor_destination_from_tmj_object]: error: guard \"object\" not met");
   }
   AllegroFlare::Layouts::Elements::CursorDestination result;

   result.tmj_object_id = object->id;
   result.name = object->name;
   result.x = object->x;
   result.y = object->y;
   result.width = object->width;
   result.height = object->height;
   result.move_up_to_target_tmj_object_id =
      extract_int_or_default(object, "move_up_to_target_id");
   result.move_down_to_target_tmj_object_id =
      extract_int_or_default(object, "move_down_to_target_id");
   result.move_left_to_target_tmj_object_id =
      extract_int_or_default(object, "move_left_to_target_id");
   result.move_right_to_target_tmj_object_id =
      extract_int_or_default(object, "move_right_to_target_id");

   return result;
}

AllegroFlare::Layouts::Elements::Frame ElementFactory::build_frame_from_tmj_object(AllegroFlare::Tiled::TMJObject* object)
{
   if (!(object))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Layouts::ElementFactory::build_frame_from_tmj_object]: error: guard \"object\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Layouts::ElementFactory::build_frame_from_tmj_object]: error: guard \"object\" not met");
   }
   AllegroFlare::Layouts::Elements::Frame result;

   result.tmj_object_id = object->id;
   result.x = object->x;
   result.y = object->y;
   result.width = object->width;
   result.height = object->height;

   return result;
}

float ElementFactory::translate_alignment_string_to_float(std::string alignment_string)
{
   // TODO: Add test
   if (alignment_string == "center") return 0.5;
   if (alignment_string == "left") return 0.0;
   if (alignment_string == "right") return 1.0;
   if (alignment_string == "bottom") return 1.0;
   if (alignment_string == "top") return 0.0;
   AllegroFlare::Logger::throw_error(
      "Layouts::Layout::translate_alignment_string_to_float",
      "Unrecognized alignment string \"" + alignment_string + "\"."
   );
   return 0.0f;
}

std::string ElementFactory::extract_color_hex_or_default(AllegroFlare::Tiled::TMJObject* object, std::string key, std::string default_fallback)
{
   AllegroFlare::Tiled::TMJObjectCustomProperties &custom_properties = object->custom_properties;

   // TODO: Add warning when present but not an int
   if (!(custom_properties.exists(key) && custom_properties.is_color(key))) return default_fallback;
   return custom_properties.get_color(key);
}

int ElementFactory::extract_int_or_default(AllegroFlare::Tiled::TMJObject* object, std::string key, int default_fallback)
{
   AllegroFlare::Tiled::TMJObjectCustomProperties &custom_properties = object->custom_properties;

   // TODO: Add warning when present but not an int
   if (!(custom_properties.exists(key) && custom_properties.is_int(key))) return default_fallback;
   return custom_properties.get_int(key);
}

int ElementFactory::extract_int_or_throw(AllegroFlare::Tiled::TMJObject* object, std::string key)
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


} // namespace Layouts
} // namespace AllegroFlare


