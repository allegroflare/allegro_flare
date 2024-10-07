

#include <AllegroFlare/Tiled/TMJDataLoader.hpp>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/StringFormatValidator.hpp>
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


TMJDataLoader::TMJDataLoader(std::string filename)
   : filename(filename)
   , num_columns(0)
   , num_rows(0)
   , tile_width(0)
   , tile_height(0)
   , layer_num_columns(0)
   , layer_num_rows(0)
   , tilelayers_tile_data({})
   , map_class("[unset-map_class]")
   , map_custom_properties({})
   , tilesets({})
   , normalize_tile_data_from_tilesets(true)
   , loaded(false)
   , objects({})
{
}


TMJDataLoader::~TMJDataLoader()
{
}


bool TMJDataLoader::get_loaded() const
{
   return loaded;
}


std::vector<AllegroFlare::Tiled::TMJObject> TMJDataLoader::get_objects() const
{
   return objects;
}


std::vector<AllegroFlare::Tiled::TMJObject> &TMJDataLoader::get_objects_ref()
{
   return objects;
}


void TMJDataLoader::for_each_object(std::function<void(AllegroFlare::Tiled::TMJObject*, void*)> function, void* user_data)
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJDataLoader::for_each_object]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJDataLoader::for_each_object]: error: guard \"loaded\" not met");
   }
   for (auto &object : objects)
   {
      function(&object, user_data);
   }
   return;
}

void TMJDataLoader::set_filename(std::string filename)
{
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJDataLoader::set_filename]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJDataLoader::set_filename]: error: guard \"(!loaded)\" not met");
   }
   this->filename = filename;
}

int TMJDataLoader::get_num_columns()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJDataLoader::get_num_columns]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJDataLoader::get_num_columns]: error: guard \"loaded\" not met");
   }
   return num_columns;
}

int TMJDataLoader::get_num_rows()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJDataLoader::get_num_rows]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJDataLoader::get_num_rows]: error: guard \"loaded\" not met");
   }
   return num_rows;
}

int TMJDataLoader::get_tile_width()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJDataLoader::get_tile_width]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJDataLoader::get_tile_width]: error: guard \"loaded\" not met");
   }
   return tile_width;
}

int TMJDataLoader::get_tile_height()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJDataLoader::get_tile_height]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJDataLoader::get_tile_height]: error: guard \"loaded\" not met");
   }
   return tile_height;
}

int TMJDataLoader::get_layer_num_columns()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJDataLoader::get_layer_num_columns]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJDataLoader::get_layer_num_columns]: error: guard \"loaded\" not met");
   }
   return layer_num_columns;
}

int TMJDataLoader::get_layer_num_rows()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJDataLoader::get_layer_num_rows]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJDataLoader::get_layer_num_rows]: error: guard \"loaded\" not met");
   }
   return layer_num_rows;
}

std::map<std::string, std::vector<int>> TMJDataLoader::get_tilelayers_tile_data()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJDataLoader::get_tilelayers_tile_data]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJDataLoader::get_tilelayers_tile_data]: error: guard \"loaded\" not met");
   }
   return tilelayers_tile_data;
}

std::string TMJDataLoader::get_map_class()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJDataLoader::get_map_class]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJDataLoader::get_map_class]: error: guard \"loaded\" not met");
   }
   return map_class;
}

AllegroFlare::Tiled::TMJObjectCustomProperties TMJDataLoader::get_map_custom_properties()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJDataLoader::get_map_custom_properties]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJDataLoader::get_map_custom_properties]: error: guard \"loaded\" not met");
   }
   return map_custom_properties;
}

std::vector<std::tuple<int, std::string, std::string>> TMJDataLoader::get_tilesets()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJDataLoader::get_tilesets]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJDataLoader::get_tilesets]: error: guard \"loaded\" not met");
   }
   return tilesets;
}

std::vector<int> TMJDataLoader::get_tilelayer_data_by_name(std::string tilelayer_name)
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJDataLoader::get_tilelayer_data_by_name]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJDataLoader::get_tilelayer_data_by_name]: error: guard \"loaded\" not met");
   }
   if (!(tilelayer_exists(tilelayer_name)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJDataLoader::get_tilelayer_data_by_name]: error: guard \"tilelayer_exists(tilelayer_name)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJDataLoader::get_tilelayer_data_by_name]: error: guard \"tilelayer_exists(tilelayer_name)\" not met");
   }
   // TODO: Test this
   // TODO: Test guards
   // TODO: Improve non-existent layer name error message
   return tilelayers_tile_data[tilelayer_name];
}

std::vector<std::vector<int>> TMJDataLoader::get_tilelayer_data_by_name_as_2d_vector(std::string tilelayer_name)
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJDataLoader::get_tilelayer_data_by_name_as_2d_vector]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJDataLoader::get_tilelayer_data_by_name_as_2d_vector]: error: guard \"loaded\" not met");
   }
   if (!(tilelayer_exists(tilelayer_name)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJDataLoader::get_tilelayer_data_by_name_as_2d_vector]: error: guard \"tilelayer_exists(tilelayer_name)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJDataLoader::get_tilelayer_data_by_name_as_2d_vector]: error: guard \"tilelayer_exists(tilelayer_name)\" not met");
   }
   // TODO: Test this
   // TODO: Test guards
   // TODO: Improve non-existent layer name error message
   std::vector<std::vector<int>> result;
   std::vector<int> &tilelayer_data = tilelayers_tile_data[tilelayer_name];
   for (int y=0; y<num_rows; y++)
   {
      result.push_back(std::vector<int>(num_columns));

      for (int x=0; x<num_columns; x++)
      {
         result.back()[x] = tilelayer_data[x + y * num_columns];
      }
   }
   return result;
}

bool TMJDataLoader::tilelayer_exists(std::string tilelayer_name)
{
   return tilelayers_tile_data.find(tilelayer_name) != tilelayers_tile_data.end();
}

bool TMJDataLoader::load()
{
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJDataLoader::load]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Tiled::TMJDataLoader::load]: error: guard \"(!loaded)\" not met");
   }
   if (!file_exists(filename))
   {
       AllegroFlare::Logger::throw_missing_file_error("AllegroFlare::Tiled::TMJDataLoader::load", filename, "tmj");
   }

   // load and validate the json data to variables
   std::ifstream i(filename);
   nlohmann::json j;
   try
   {
      i >> j;
   }
   catch (const std::exception& e)
   {
      i.close();
      std::stringstream error_message;
      error_message << "[AllegroFlare::Tiled::TMJDataLoader::load()]: error: The file "
                    << "\"" << filename << "\" appears to have"
                    << " malformed JSON. The following error was thrown by nlohmann::json: \""
                    << e.what() << "\"";
      throw std::runtime_error(error_message.str());
   }

   num_columns = j["width"]; // get width
   num_rows = j["height"]; // get height
   tile_width = j["tilewidth"]; // get width
   tile_height = j["tileheight"]; // get height



   // Obtain the list of "tilesets" (note that multiple tilesets might be used. In the tile data, the value used
   // on each tile is relative to the "firstgid" for that tileset.
   std::vector<std::pair<std::string, int>> tilesets_info; // *source*, *firstgid*
   std::set<int> tilesets_gids;
   if (!j.contains("tilesets"))
   {
      // TODO: Test this throw
      AllegroFlare::Logger::warn_from(
         "AllegroFlare::Tiled::TMJDataLoader::load",
         "Expecting tmj file to contain a root-level \"tilesets\" property when loading \""
            + filename + "\", but it does not exist."
      );
   }
   else
   {
      // TODO: Validate "tilesets" is an array
      for (auto &tileset : j["tilesets"].items())
      {
         int firstgid = tileset.value()["firstgid"];
         //firstgid -= 1; // NOTE: note the -1 here

         tilesets_info.push_back({
            tileset.value()["source"],
            firstgid
         });
         tilesets_gids.insert(firstgid);
      }
   }



   // Extract map "class" (or set to blank if it's not present)
   if (!j.contains("class"))
   {
      map_class = "";
   }
   else
   {
      map_class = j["class"].get<std::string>();
   }


   // Extract map custom properties
   map_custom_properties = attempt_to_extract_custom_properties(&j);




   // Extract the tilesets
   if (!j.contains("tilesets"))
   {
      AllegroFlare::Logger::warn_from(
         "AllegroFlare::Tiled::TMJDataLoader::load",
         "The map does not contain any section \"tilesets\". If this is expected behavior please ignore this "
            "warning message. TODO: Add option to disable this warning."
      );
   }
   else
   {
      if (!j["tilesets"].is_array())
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Tiled::TMJDataLoader::load",
            "The section \"tilesets\" is present but is not an array."
         );
      }
      
      for (auto &tileset : j["tilesets"].items())
      {
         int firstgid = tileset.value()["firstgid"].get<int>();
         std::string source = tileset.value()["source"].get<std::string>();

         tilesets.push_back(
            std::tuple<int, std::string, std::string>{
               firstgid,
               source,
               extract_last_fragment(source)
            }
         );
      }
   }



   //layer_num_columns = tilelayer["width"];
   //layer_num_rows = tilelayer["height"];
   //layer_tile_data = tilelayer["data"].get<std::vector<int>>();
   if (normalize_tile_data_from_tilesets)
   {
      // TODO: Test this normalization is correct with multiple tilesets
      //layer_tile_data = normalize_tile_data_to_tilesets_firstgids(
            //layer_tile_data,
            //tilesets_gids
         //);

      //background_tilelayer_tile_data = normalize_tile_data_to_tilesets_firstgids(
            //background_tilelayer_tile_data,
            //tilesets_gids
         //);

      //foreground_tilelayer_tile_data = normalize_tile_data_to_tilesets_firstgids(
            //foreground_tilelayer_tile_data,
            //tilesets_gids
         //);
   }


   //
   // Collision tile layer
   //




   // TODO: Consider adding this feature when getting collision layer data


   //if (reduce_any_non_zero_collision_layer_data_to_1)
   //{
      //std::set<int> modified_values;
      //for (auto &collision_layer_tile_datum : collision_layer_tile_data)
      //{
         //if (collision_layer_tile_datum > 1)
         //{
            //modified_values.insert(collision_layer_tile_datum);
            //collision_layer_tile_datum = 1;
         //}
      //}

      //if (!modified_values.empty())
      //{
         //// Convert the list to a string
         //std::ostringstream oss;
         //for (auto it = modified_values.begin(); it != modified_values.end(); ++it)
         //{
            //oss << *it;
            //if (std::next(it) != modified_values.end()) {
               //oss << ", ";
            //}
         //}
         //std::string list_of_modified_values = oss.str();

         //AllegroFlare::Logger::warn_from(
            //"AllegroFlare::Tiled::TMJDataLoader::load",
            //"Note that reduce_any_non_zero_collision_layer_data_to_1 is set to \"true\", and during processing "
               //"the following values were found and truncated to 1: [ " + list_of_modified_values + " ]."
         //);
      //}
   //}






   // Load *all* tile layers
   {
      //bool collision_tilelayer_type_found = false;
      int layer_num_columns = 0;
          //type: int
          //init_with: 0
          //getter: explicit

       int layer_num_rows = 0;
          //type: int
          //init_with: 0
          //getter: explicit

        std::vector<int> layer_tile_data;
        //- name:
         //collision_layer_tile_data
          //type: std::vector<int>
          //init_with: '{}'
          //getter: explicit
      nlohmann::json tilelayer;
      std::string tilelayer_name;
      std::string layer_name;

      for (auto &layer : j["layers"].items())
      {
         if (layer.value()["type"] != "tilelayer") continue; // && layer.value()["name"] == "collision")
         //{
            tilelayer = layer.value();
            tilelayer_name = layer.value()["name"];
            //tilelayer_type_found = true;
            //break;
         //}
      //}

         layer_num_columns = tilelayer["width"];
         layer_num_rows = tilelayer["height"];
         layer_tile_data = tilelayer["data"].get<std::vector<int>>();

         if (normalize_tile_data_from_tilesets)
         {
            // TODO: Test this normalization is correct with multiple tilesets
            layer_tile_data = normalize_tile_data_to_tilesets_firstgids(
                  layer_tile_data,
                  tilesets_gids
               );
         }

         tilelayers_tile_data[tilelayer_name] = layer_tile_data;
      }

      // HERE
      //- name: tilelayers_tile_data
        //type: std::map<std::string, std::vector<int>>
        //init_with: '{}'
        //getter: explicit
      //tilelayers_tile_data[tilelayer_name] = layer_tile_data;
   }



   // Load the object layers
   for (auto &layer : j["layers"].items())
   {
      if (layer.value()["type"] == "objectgroup")
      {
         auto &object_layer_json = layer.value();

         if (!object_layer_json.contains("name"))
         {
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::Tiled::TMJDataLoader::load",
               "When parsing an \"objectgroup\" type layer, expecting a property of type \"name\" but it does not "
                  "exist."
            );
         }

         std::string object_layer_name = object_layer_json["name"].get<std::string>();

         if (!object_layer_json.contains("objects"))
         {
            std::stringstream error_message;
            error_message << "Expecting [\"objects\"] to exist in the \"objectgoup\"-type layer, but it does not.";
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::Tiled::TMJDataLoader::load",
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
                  "AllegroFlare::Tiled::TMJDataLoader::load",
                  "When parsing properties on an object, expecting to find \"class\" or \"type\" but neither was "
                     "present. This error occurred while loading \"" + filename + "\"."
               );
            }

            // Extract the "type". Note that different versions of Tiled have swapped "class" and "type" as the
            // keys for this value.
            std::string type_property;
            if (object_json.value().contains("class")) type_property =
               object_json.value()["class"].get<std::string>();
            else if (object_json.value().contains("type")) type_property =
               object_json.value()["type"].get<std::string>();

            std::string name_property = object_json.value()["name"].get<std::string>();
            int id_property = object_json.value()["id"].get<int>();
            float x_property = object_json.value()["x"].get<float>();
            float y_property = object_json.value()["y"].get<float>();
            float width_property = object_json.value()["width"].get<float>();
            float height_property = object_json.value()["height"].get<float>();
            std::vector<AllegroFlare::Vec2D> polygon = {};
            AllegroFlare::Tiled::TMJObjectCustomProperties custom_properties;

            // Load the "polygon" vertices
            if (object_json.value().contains("polygon"))
            {
               if (!object_json.value()["polygon"].is_array())
               {
                  throw std::runtime_error("AllegroFlare::Tiled::TMJDataLoader: polygon is not array");
               }

               for (auto &polygon_point : object_json.value()["polygon"].items())
               {
                  if (!polygon_point.value().contains("x") || !polygon_point.value().contains("y"))
                  {
                     throw std::runtime_error("AllegroFlare::Tiled::TMJDataLoader: polygon point does not contain "
                        "\"x\", \"y\")");
                  }
                  float x = polygon_point.value()["x"].get<float>();
                  float y = polygon_point.value()["y"].get<float>();
                  polygon.push_back({x, y});
               }
            }

            /*
            // Load custom properties
            if (object_json.value().contains("properties"))
            {
               // TODO: Improve this error message
               if (!object_json.value()["properties"].is_array())
               {
                  throw std::runtime_error("3j4io5jio3j5o2: is not array");
               }

               for (auto &custom_property_item : object_json.value()["properties"].items())
               //for (auto &custom_property_item : values["properties"].items())
               {
                  nlohmann::json custom_property = custom_property_item.value();
                  std::string custom_property_name = custom_property["name"];

                  if (!custom_property.contains("type"))
                  {
                     AllegroFlare::Logger::throw_error(
                        "AllegroFlare::Tiled::TMJDataLoader::load",
                        "When parsing custom properties on an object, expecting to find \"type\" but it was not "
                           "present. This error occurred while loading \"" + filename + "\"."
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
                           "AllegroFlare::Tiled::TMJDataLoader::load",
                           "When loading custom properies, the property name \"" + custom_property_type + "\" was "
                              "parsed with value of \"0\", indicating that it is empty (or unset) in Tiled. The "
                              "loader will skip over including this property internally."
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
                        "AllegroFlare::Tiled::TMJDataLoader::load",
                        "When loading custom properies, an object contained a custom property of type \"" +
                           custom_property_type + "\" which is not handled here."
                     );
                  }
               }
            }
            */

            // TODO: Test this
            custom_properties = attempt_to_extract_custom_properties(&object_json.value());

            objects.push_back({});
            auto &object = objects.back();

            object.id = id_property;
            object.type = type_property;
            object.x = x_property;
            object.y = y_property;
            object.width = width_property;
            object.height = height_property;
            object.name = name_property;
            object.object_layer_name = object_layer_name;
            object.polygon = polygon;
            object.custom_properties = custom_properties;
         }
      }
   }

   loaded = true;

   i.close();

   return true;
}

std::string TMJDataLoader::extract_last_fragment(std::string path_string)
{
   size_t last_slash_pos = path_string.find_last_of("/");

   // Extract the substring after the last '/'
   if (last_slash_pos == std::string::npos)
   {
      //return path_string.substr(last_slash_pos + 1);
   //}
      AllegroFlare::Logger::warn_from(
         "AllegroFlare::Tiled::TMJDataLoader::extract_last_fragment",
         "When attempting to extract the image filename from the path string \"" + path_string + "\", one could "
            "not be captured. If this is a real file path, this method should be updated to account for it, "
            "and for now the image filename will not be known and will be blank."
      );
   }
   else
   {
      return path_string.substr(last_slash_pos + 1);
   }
   return "";
}

AllegroFlare::Tiled::TMJObjectCustomProperties TMJDataLoader::attempt_to_extract_custom_properties(nlohmann::json* object_json)
{
   AllegroFlare::Tiled::TMJObjectCustomProperties custom_properties;

   // Load custom properties
   //if (object_json.value().contains("properties"))
   if (object_json->contains("properties"))
   {
      // TODO: Improve this error message
      //if (!object_json.value()["properties"].is_array())
      if (!object_json->operator[]("properties").is_array())
      {
         throw std::runtime_error("3j4io5jio3j5o2: is not array");
      }

      //for (auto &custom_property_item : object_json.value()["properties"].items())
      for (auto &custom_property_item : object_json->operator[]("properties").items())
      //for (auto &custom_property_item : values["properties"].items())
      {
         nlohmann::json custom_property = custom_property_item.value();
         std::string custom_property_name = custom_property["name"];

         if (!custom_property.contains("type"))
         {
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::Tiled::TMJDataLoader::load",
               "When parsing custom properties on an object, expecting to find \"type\" but it was not "
                  "present. This error occurred while loading \"" + filename + "\"."
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
                  "AllegroFlare::Tiled::TMJDataLoader::load",
                  "When loading custom properies, the property name \"" + custom_property_type + "\" was "
                     "parsed with value of \"0\", indicating that it is empty (or unset) in Tiled. The "
                     "loader will skip over including this property internally."
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
               "AllegroFlare::Tiled::TMJDataLoader::load",
               "When loading custom properies, an object contained a custom property of type \"" +
                  custom_property_type + "\" which is not handled here."
            );
         }
      }
   }
   return custom_properties;
}

std::vector<int> TMJDataLoader::normalize_tile_data_to_tilesets_firstgids(std::vector<int> data, std::set<int> tilesets_firstgids)
{
   for (auto &datum : data)
   {
      for (auto rit = tilesets_firstgids.rbegin(); rit != tilesets_firstgids.rend(); ++rit)
      {
         if (datum >= *rit)
         {
            datum = datum - *rit + 1; // TODO: Test this calculation is correct
            goto out;
         }
      }
      out:
   }
   return data;
}

bool TMJDataLoader::file_exists(std::string filename)
{
   return std::filesystem::exists(filename);
}


} // namespace Tiled
} // namespace AllegroFlare


