

#include <AllegroFlare/Tiled/TMJImageLayerLoader.hpp>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/Tiled/TMJDataLoader.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <lib/nlohmann/json.hpp>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Tiled
{


TMJImageLayerLoader::TMJImageLayerLoader(std::string filename)
   : filename(filename)
   , image_layers({})
   , loaded(false)
{
}


TMJImageLayerLoader::~TMJImageLayerLoader()
{
}


void TMJImageLayerLoader::for_each_image_layer(std::function<void(AllegroFlare::Tiled::TMJImageLayer*, void*)> function, void* user_data)
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJImageLayerLoader::for_each_image_layer]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJImageLayerLoader::for_each_image_layer]: error: guard \"loaded\" not met");
   }
   for (auto &image_layer : image_layers)
   {
      function(&image_layer, user_data);
   }
   return;
}

std::vector<AllegroFlare::Tiled::TMJImageLayer> TMJImageLayerLoader::get_image_layers()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJImageLayerLoader::get_image_layers]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJImageLayerLoader::get_image_layers]: error: guard \"loaded\" not met");
   }
   return image_layers;
}

void TMJImageLayerLoader::load()
{
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJImageLayerLoader::load]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJImageLayerLoader::load]: error: guard \"(!loaded)\" not met");
   }
   if (!file_exists(filename))
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Tiled::TMJImageLayerLoader::load",
         "The file \"" + filename + "\" does not exist."
      );
   }

   // load and validate the json data to variables
   std::ifstream i(filename);
   nlohmann::json source_json;
   try
   {
      i >> source_json;
   }
   catch (const std::exception& e)
   {
      i.close();
      //std::stringstream error_message;
      //error_message << "The file \"" << filename << "\" appears to have malformed JSON. The following error was "
                    //<< "thrown by nlohmann::json: \"" << e.what() << "\"";
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Tiled::TMJImageLayerLoader::load",
         "The file \"" + filename + "\" appears to have malformed JSON. The following error was thrown by "
            "nlohmann::json: \"" + e.what() + "\""
      );
   }
   i.close();


   // TODO: Account for nested "group" layer that may contain image layers

   bool image_layer_type_found = false;
   std::vector<nlohmann::json> image_layers_json;
   for (auto &layer : source_json["layers"].items())
   {
      if (layer.value()["type"] == "imagelayer")
      {
         image_layers_json.push_back(layer.value());
         image_layer_type_found = true;
      }
   }

   // Validate image layers found
   if (!image_layer_type_found)
   {
      AllegroFlare::Logger::warn_from(
         "AllegroFlare::Tiled::TMJImageLayerLoader::load",
         "When loading TMJ file \"" + filename + "\". There were no layers of type \"imagelayer\". Skipping."
      );
      loaded = true;
   }


   // Load the image layers one by one
   ALLEGRO_COLOR default_color = AllegroFlare::Tiled::TMJImageLayer::DEFAULT_TINT_COLOR;
   for (auto &image_layer_json : image_layers_json)
   {
       std::string name = obtain_string_or_throw("name", &image_layer_json);

       AllegroFlare::Logger::info_from(
         "AllegroFlare::Tiled::TMJImageLayerLoader::load",
          "Loading layer named \"" + name + "\" from TMJ file \"" + filename + "\"."
       );

       std::string image_filename = obtain_string_or_throw("image", &image_layer_json);
       int id = obtain_int_or_throw("id", &image_layer_json);
       float offset_x = obtain_float_or_default("offsetx", &image_layer_json, 0.0f);
       float offset_y = obtain_float_or_default("offsety", &image_layer_json, 0.0f);
       float parallax_x = obtain_float_or_default("parallaxx", &image_layer_json, 1.0f);
       float parallax_y = obtain_float_or_default("parallaxy", &image_layer_json, 1.0f);
       bool repeat_x = obtain_bool_or_default("repeatx", &image_layer_json, false);
       bool repeat_y = obtain_bool_or_default("repeaty", &image_layer_json, false);
       float opacity = obtain_float_or_default("opacity", &image_layer_json, 1.0f);
       bool tint_color_is_set = image_layer_json.contains("tintcolor");
       ALLEGRO_COLOR tint_color = obtain_color_or_default("tintcolor", &image_layer_json, default_color);

       image_layers.push_back(AllegroFlare::Tiled::TMJImageLayer(
          id,
          name,
          image_filename,
          offset_x,
          offset_y,
          parallax_x,
          parallax_y,
          repeat_x,
          repeat_y,
          opacity, // TODO: Check if this is a float when loaded from TMJ
          tint_color_is_set,
          tint_color
       ));
   }

   loaded = true;

   return;
}

std::string TMJImageLayerLoader::obtain_string_or_throw(std::string key, nlohmann::json* object_json)
{
   if (!(object_json))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJImageLayerLoader::obtain_string_or_throw]: error: guard \"object_json\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJImageLayerLoader::obtain_string_or_throw]: error: guard \"object_json\" not met");
   }
   if (!object_json->contains(key))
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Tiled::TMJImageLayerLoader::obtain_string_or_throw",
         "When parsing an \"imagelayer\" type layer, expecting a property with key \"" + key + "\" but it was not "
            "present."
      );
   }
   // TODO: validate is string
   std::string value = object_json->operator[](key).get<std::string>();
   return value;
}

float TMJImageLayerLoader::obtain_float_or_throw(std::string key, nlohmann::json* object_json)
{
   if (!(object_json))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJImageLayerLoader::obtain_float_or_throw]: error: guard \"object_json\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJImageLayerLoader::obtain_float_or_throw]: error: guard \"object_json\" not met");
   }
   if (!object_json->contains(key))
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Tiled::TMJImageLayerLoader::obtain_float_or_throw",
         "When parsing an \"imagelayer\" type layer, expecting a property with key \"" + key + "\" but it was not "
            "present."
      );
   }
   // TODO: validate is float
   float value = object_json->operator[](key).get<float>();
   return value;
}

float TMJImageLayerLoader::obtain_float_or_default(std::string key, nlohmann::json* object_json, float default_value)
{
   if (!(object_json))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJImageLayerLoader::obtain_float_or_default]: error: guard \"object_json\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJImageLayerLoader::obtain_float_or_default]: error: guard \"object_json\" not met");
   }
   if (!object_json->contains(key)) return default_value;
   // TODO: validate is float
   float value = object_json->operator[](key).get<float>();
   return value;
}

ALLEGRO_COLOR TMJImageLayerLoader::obtain_color_or_default(std::string key, nlohmann::json* object_json, ALLEGRO_COLOR default_value)
{
   if (!(object_json))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJImageLayerLoader::obtain_color_or_default]: error: guard \"object_json\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJImageLayerLoader::obtain_color_or_default]: error: guard \"object_json\" not met");
   }
   if (object_json->contains(key))
   {
      ALLEGRO_COLOR result_color;
      std::string color_as_hex_string = object_json->operator[](key).get<std::string>();
      std::tuple<float, float, float, float> extracted_rgba_f =
         AllegroFlare::Tiled::TMJDataLoader::convert_hex_to_rgba_f(color_as_hex_string);
      float alpha = std::get<3>(extracted_rgba_f);

      result_color.r = std::get<0>(extracted_rgba_f) * alpha;
      result_color.g = std::get<1>(extracted_rgba_f) * alpha;
      result_color.b = std::get<2>(extracted_rgba_f) * alpha;
      result_color.a = alpha;

      return result_color;
   }
   return default_value;
}

bool TMJImageLayerLoader::obtain_bool_or_default(std::string key, nlohmann::json* object_json, bool default_value)
{
   if (!(object_json))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJImageLayerLoader::obtain_bool_or_default]: error: guard \"object_json\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJImageLayerLoader::obtain_bool_or_default]: error: guard \"object_json\" not met");
   }
   if (!object_json->contains(key)) return default_value;
   // TODO: validate is bool
   bool value = object_json->operator[](key).get<bool>();
   return value;
}

int TMJImageLayerLoader::obtain_int_or_throw(std::string key, nlohmann::json* object_json)
{
   if (!(object_json))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJImageLayerLoader::obtain_int_or_throw]: error: guard \"object_json\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJImageLayerLoader::obtain_int_or_throw]: error: guard \"object_json\" not met");
   }
   if (!object_json->contains(key))
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Tiled::TMJImageLayerLoader::obtain_int_or_throw",
         "When parsing an \"imagelayer\" type layer, expecting a property with key \"" + key + "\" but it was not "
            "present."
      );
   }
   // TODO: validate is int
   int value = object_json->operator[](key).get<int>();
   return value;
}

void TMJImageLayerLoader::attempt_to_extract_custom_properties()
{
   // NOTE: This method is currently empty here, but an implementation exists in
   // AllegroFlare::Tiled::TMJDataLoader::attempt_to_extract_custom_properties, though it is currently not static
   // and will need to be made static.

   // AllegroFlare::Prototypes::Platforming2D::TMJObjectLoaderObjectCustomProperties custom_properties = ...
   return;
}

bool TMJImageLayerLoader::file_exists(std::string filename)
{
   return std::filesystem::exists(filename);
}


} // namespace Tiled
} // namespace AllegroFlare


