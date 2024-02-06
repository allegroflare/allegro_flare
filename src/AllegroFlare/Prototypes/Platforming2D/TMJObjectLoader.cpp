

#include <AllegroFlare/Prototypes/Platforming2D/TMJObjectLoader.hpp>

#include <AllegroFlare/Logger.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <lib/nlohmann/json.hpp>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace Platforming2D
{


TMJObjectLoader::TMJObjectLoader(std::string filename)
   : filename(filename)
   , object_parsed_callback({})
   , object_parsed_callback_user_data(nullptr)
   , loaded(false)
{
}


TMJObjectLoader::~TMJObjectLoader()
{
}


void TMJObjectLoader::set_object_parsed_callback(std::function<void(std::string, float, float, float, float, int, AllegroFlare::Prototypes::Platforming2D::TMJObjectLoaderObjectCustomProperties, void*)> object_parsed_callback)
{
   this->object_parsed_callback = object_parsed_callback;
}


void TMJObjectLoader::set_object_parsed_callback_user_data(void* object_parsed_callback_user_data)
{
   this->object_parsed_callback_user_data = object_parsed_callback_user_data;
}


std::function<void(std::string, float, float, float, float, int, AllegroFlare::Prototypes::Platforming2D::TMJObjectLoaderObjectCustomProperties, void*)> TMJObjectLoader::get_object_parsed_callback() const
{
   return object_parsed_callback;
}


void* TMJObjectLoader::get_object_parsed_callback_user_data() const
{
   return object_parsed_callback_user_data;
}


void TMJObjectLoader::load()
{
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[TMJObjectLoader::load]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJObjectLoader::load: error: guard \"(!loaded)\" not met");
   }
   if (!file_exists(filename))
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Prototypes::Platforming2D::TMJObjectLoader::load",
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
      std::stringstream error_message;
      error_message << "The file \"" << filename << "\" appears to have malformed JSON. The following error was "
                    << "thrown by nlohmann::json: \"" << e.what() << "\"";
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Prototypes::Platforming2D::TMJObjectLoader::load",
         error_message.str()
      );
   }
   i.close();


   // TODO: validate there is one and only "objectgroup" layer

   // get first j["layers"] that is a ["type"] == "objectgroup"
   bool object_layer_type_found = false;
   nlohmann::json object_layer_json;
   for (auto &layer : source_json["layers"].items())
   {
      if (layer.value()["type"] == "objectgroup")
      {
         object_layer_json = layer.value();
         object_layer_type_found = true;
         break;
      }
   }
   if (!object_layer_type_found)
   {
      // TODO: Swap this error message with AllegroFlare::Errors
      throw std::runtime_error("TMJObjectLoader: error: layer of type \"objectgroup\" not found.");
   }


   // load the objects one by one

   if (!object_layer_json.contains("objects"))
   {
      std::stringstream error_message;
      error_message << "Expecting [\"objects\"] to exist in the \"objectgoup\"-type layer, but it does not.";
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Prototypes::Platforming2D::TMJObjectLoader",
         error_message.str()
      );
   }
   for (auto &object_json : object_layer_json["objects"].items())
   {
      // Note that for compatibility reasons with Tiled, both "class" and "type" are used as possible keys.
      // Depending on the version of Tiled that exported the format, one or the other could have been used.
      // Here in AllegroFlare, it us currently referred to it as "type", which is the correct Tiled name for the
      // property.  Note that for a temporary period it was changed to "class" in Tiled.
      // See this issue for more info: https://github.com/mapeditor/tiled/issues/3492

      // TODO: Throw error if "class" is present, advise to rename/update to "type"
      if (!object_json.value().contains("class") && !object_json.value().contains("type"))
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Prototypes::Platforming2D::TMJObjectLoader::load",
            "When parsing properties on an object, expecting to find \"class\" or \"type\" but neither was present. "
               "This error occurred while loading \"" + filename + "\"."
         );
      }

      std::string type_property;

      if (object_json.value().contains("class")) type_property = object_json.value()["class"].get<std::string>();
      else if (object_json.value().contains("type")) type_property = object_json.value()["type"].get<std::string>();

      int id_property = object_json.value()["id"].get<int>();
      float x_property = object_json.value()["x"].get<float>();
      float y_property = object_json.value()["y"].get<float>();
      float width_property = object_json.value()["width"].get<float>();
      float height_property = object_json.value()["height"].get<float>();
      AllegroFlare::Prototypes::Platforming2D::TMJObjectLoaderObjectCustomProperties custom_properties;

      if (object_json.value().contains("properties"))
      {
         // TODO: Improve this error message
         if (!object_json.value()["properties"].is_array()) throw std::runtime_error("3j4io5jio3j5o2: is not array");

         for (auto &custom_property_item : object_json.value()["properties"].items())
         //for (auto &custom_property_item : values["properties"].items())
         {
            nlohmann::json custom_property = custom_property_item.value();
            std::string custom_property_name = custom_property["name"];

            if (!custom_property.contains("type"))
            {
               AllegroFlare::Logger::throw_error(
                  "AllegroFlare::Prototypes::Platforming2D::TMJObjectLoader::load",
                  "When parsing custom properties on an object, expecting to find \"type\" but it was not present. "
                     "This error occurred while loading \"" + filename + "\"."
               );
            }

            std::string custom_property_type = custom_property["type"];

            // TODO: Test the parsing of these custom values
            if (custom_property_type == "string")
            {
               std::string custom_property_value = custom_property["value"];
               custom_properties.add_string(custom_property_name, custom_property_value);
            }
            else if (custom_property_type == "int")
            {
               int custom_property_value = custom_property["value"];
               custom_properties.add_int(custom_property_name, custom_property_value);
            }
            else if (custom_property_type == "float")
            {
               float custom_property_value = custom_property["value"];
               custom_properties.add_float(custom_property_name, custom_property_value);
            }
            else if (custom_property_type == "bool")
            {
               bool custom_property_value = custom_property["value"];
               custom_properties.add_bool(custom_property_name, custom_property_value);
            }
            else if (custom_property_type == "object")
            {
               int custom_property_value = custom_property["value"];
               if (custom_property_value == 0)
               {
                  AllegroFlare::Logger::warn_from(
                     "AllegroFlare::Prototypes::Platforming2D::TMJObjectLoader::load",
                     "When loading custom properies, the property name \"" + custom_property_type + "\" was parsed "
                        "with value of \"0\", indicating that it is empty (or unset) in Tiled. The loader will skip "
                        "over including this property internally."
                  );
               }
               else
               {
                  custom_properties.add_int(custom_property_name, custom_property_value);
               }
            }
            else
            {
               AllegroFlare::Logger::throw_error(
                  "AllegroFlare::Prototypes::Platforming2D::TMJObjectLoader::load",
                  "When loading custom properies, an object contained a custom property of type \"" +
                     custom_property_type + "\" which is not handled here."
               );
            }
         }
      }

      // call the callback (if present)
      if (object_parsed_callback)
      {
         object_parsed_callback(
            type_property,
            x_property,
            y_property,
            width_property,
            height_property,
            id_property,
            custom_properties,
            object_parsed_callback_user_data
         );
      }
   }



   return;
}

bool TMJObjectLoader::file_exists(std::string filename)
{
   return std::filesystem::exists(filename);
}


} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


