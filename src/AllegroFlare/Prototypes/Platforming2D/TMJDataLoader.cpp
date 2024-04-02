

#include <AllegroFlare/Prototypes/Platforming2D/TMJDataLoader.hpp>

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
namespace Prototypes
{
namespace Platforming2D
{


TMJDataLoader::TMJDataLoader(std::string filename)
   : filename(filename)
   , num_columns(0)
   , num_rows(0)
   , tile_width(0)
   , tile_height(0)
   , layer_num_columns(0)
   , layer_num_rows(0)
   , layer_tile_data({})
   , collision_layer_num_columns(0)
   , collision_layer_num_rows(0)
   , collision_layer_tile_data({})
   , normalize_tile_data_from_tilesets(true)
   , reduce_any_non_zero_collision_layer_data_to_1(true)
   , loaded(false)
{
}


TMJDataLoader::~TMJDataLoader()
{
}


bool TMJDataLoader::get_loaded() const
{
   return loaded;
}


int TMJDataLoader::get_num_columns()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[TMJDataLoader::get_num_columns]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJDataLoader::get_num_columns: error: guard \"loaded\" not met");
   }
   return num_columns;
}

int TMJDataLoader::get_num_rows()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[TMJDataLoader::get_num_rows]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJDataLoader::get_num_rows: error: guard \"loaded\" not met");
   }
   return num_rows;
}

int TMJDataLoader::get_tile_width()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[TMJDataLoader::get_tile_width]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJDataLoader::get_tile_width: error: guard \"loaded\" not met");
   }
   return tile_width;
}

int TMJDataLoader::get_tile_height()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[TMJDataLoader::get_tile_height]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJDataLoader::get_tile_height: error: guard \"loaded\" not met");
   }
   return tile_height;
}

int TMJDataLoader::get_layer_num_columns()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[TMJDataLoader::get_layer_num_columns]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJDataLoader::get_layer_num_columns: error: guard \"loaded\" not met");
   }
   return layer_num_columns;
}

int TMJDataLoader::get_layer_num_rows()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[TMJDataLoader::get_layer_num_rows]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJDataLoader::get_layer_num_rows: error: guard \"loaded\" not met");
   }
   return layer_num_rows;
}

std::vector<int> TMJDataLoader::get_layer_tile_data()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[TMJDataLoader::get_layer_tile_data]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJDataLoader::get_layer_tile_data: error: guard \"loaded\" not met");
   }
   return layer_tile_data;
}

int TMJDataLoader::get_collision_layer_num_columns()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[TMJDataLoader::get_collision_layer_num_columns]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJDataLoader::get_collision_layer_num_columns: error: guard \"loaded\" not met");
   }
   return collision_layer_num_columns;
}

int TMJDataLoader::get_collision_layer_num_rows()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[TMJDataLoader::get_collision_layer_num_rows]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJDataLoader::get_collision_layer_num_rows: error: guard \"loaded\" not met");
   }
   return collision_layer_num_rows;
}

std::vector<int> TMJDataLoader::get_collision_layer_tile_data()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[TMJDataLoader::get_collision_layer_tile_data]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJDataLoader::get_collision_layer_tile_data: error: guard \"loaded\" not met");
   }
   return collision_layer_tile_data;
}

bool TMJDataLoader::load()
{
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[TMJDataLoader::load]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJDataLoader::load: error: guard \"(!loaded)\" not met");
   }
   if (!file_exists(filename))
   {
      AllegroFlare::Logger::throw_missing_file_error("Platforming2D::TMJDataLoader::load()", filename, "tmj");
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
      error_message << "[Platforming2D::TMJDataLoader::load()]: error: The file "
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
         "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader",
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


   bool tilelayer_type_found = false;
   nlohmann::json tilelayer;

   // First, look for a tilelayer type named "terrain"
   // TODO: Test this behavior
   for (auto &layer : j["layers"].items())
   {
      std::string layer_name = layer.value()["name"];

      if (layer_name != "terrain") continue;

      if (layer.value()["type"] != "tilelayer")
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
            "Found a layer named \"terrain\" but it was expected to be a \"tilelayer\" type layer and was not."
         );
      }

      tilelayer = layer.value();
      tilelayer_type_found = true;
      AllegroFlare::Logger::info_from(
         "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
         "Found layer \"" + layer_name + "\" to use as visual tile layer."
      );
      break;
   }

   // If no "terrain" layer was found of type "tilelayer", look for the first "tilelayer" that does not have
   // excluding features.
   if (!tilelayer_type_found)
   {
      AllegroFlare::Logger::info_from(
         "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
         "Looking for \"tilelayer\" named \"terrain\" but it was not found. As a backup, now looking for the first "
            "of type \"tilelayer\" that does not have any excluding traits."
      );
      // Get first layer that is of type "tilelayer" (and not named "collision", and not postfixed with "_buffer")

      for (auto &layer : j["layers"].items())
      {
         if (layer.value()["type"] != "tilelayer") continue;
         if (layer.value()["name"] == "collision") continue;
         //if (layer.value()["name"] == "collision") continue;

         // If the layer name is postfixed with "_buffer", skip
         std::string layer_name = layer.value()["name"];
         AllegroFlare::StringFormatValidator validator(layer_name);

         if (validator.ends_with("_buffer") || validator.ends_with("_prototype"))
         {
            AllegroFlare::Logger::info_from(
               "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
               "Skipping over layer named \"" + layer_name + "\" as possible candidate for visual tile "
                  "layer loading."
            );
            continue;
         }

         tilelayer = layer.value();
         tilelayer_type_found = true;
         AllegroFlare::Logger::info_from(
            "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
            "Found layer \"" + layer_name + "\" to use as visual tile layer."
         );
         break;
      }
   }

   // Throw if an appropriate tilelayer was never found
   if (!tilelayer_type_found)
   {
      throw std::runtime_error("TMJMeshLoader: error: tilelayer for visual tiles was not found.");
   }

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



   // Get the first layer named "collision"

   bool collision_tilelayer_type_found = false;
   nlohmann::json collision_tilelayer;
   for (auto &layer : j["layers"].items())
   {
      if (layer.value()["type"] == "tilelayer" && layer.value()["name"] == "collision")
      {
         collision_tilelayer = layer.value();
         collision_tilelayer_type_found = true;
         break;
      }
   }
   if (!collision_tilelayer_type_found)
   {
      std::stringstream error_message;
      error_message << "TMJMeshLoader: error: collision_tilelayer type not found. Expecting a layer of type "
                    << "\"tilelayer\" that also has a \"name\" property of \"collision\". Note that only "
                    << "the following layers present: \"" << std::endl;
      int layer_num = 0;
      for (auto &layer : j["layers"].items())
      {
         layer_num++;
         error_message << "  - layer " << layer_num << ":" << std::endl;
         error_message << "    - type: \"" << layer.value()["type"] << "\"" << std::endl;
         error_message << "    - name: \"" << layer.value()["name"] << "\"" << std::endl;
      }
      throw std::runtime_error(error_message.str());
   }

   collision_layer_num_columns = collision_tilelayer["width"];
   collision_layer_num_rows = collision_tilelayer["height"];
   collision_layer_tile_data = collision_tilelayer["data"].get<std::vector<int>>();

   if (normalize_tile_data_from_tilesets)
   {
      // TODO: Test this normalization is correct with multiple tilesets
      collision_layer_tile_data = normalize_tile_data_to_tilesets_firstgids(
            collision_layer_tile_data,
            tilesets_gids
         );
   }

   if (reduce_any_non_zero_collision_layer_data_to_1)
   {
      std::set<int> modified_values;
      for (auto &collision_layer_tile_datum : collision_layer_tile_data)
      {
         if (collision_layer_tile_datum > 1)
         {
            modified_values.insert(collision_layer_tile_datum);
            collision_layer_tile_datum = 1;
         }
      }

      if (!modified_values.empty())
      {
         // Convert the list to string
         std::ostringstream oss;
         for (auto it = modified_values.begin(); it != modified_values.end(); ++it)
         {
            oss << *it;
            if (std::next(it) != modified_values.end()) {
               oss << ", ";
            }
         }
         std::string list_of_modified_values = oss.str();

         AllegroFlare::Logger::warn_from(
            "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
            "Note that reduce_any_non_zero_collision_layer_data_to_1 is set to \"true\", and during processing "
               "the following values were found and truncated to 1: [ " + list_of_modified_values + " ]."
         );
      }
   }

   loaded = true;

   i.close();

   return true;
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


} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


