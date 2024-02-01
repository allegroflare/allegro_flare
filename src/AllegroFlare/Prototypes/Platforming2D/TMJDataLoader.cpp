

#include <AllegroFlare/Prototypes/Platforming2D/TMJDataLoader.hpp>

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

         tilesets_info.push_back({
            tileset.value()["source"],
            firstgid
         });
         tilesets_gids.insert(firstgid);
      }
   }


   // Get first layer that is of type "tilelayer" (and not named "collision")

   bool tilelayer_type_found = false;
   nlohmann::json tilelayer;
   for (auto &layer : j["layers"].items())
   {
      if (layer.value()["type"] == "tilelayer" && layer.value()["name"] != "collision")
      {
         tilelayer = layer.value();
         tilelayer_type_found = true;
         break;
      }
   }
   if (!tilelayer_type_found) throw std::runtime_error("TMJMeshLoader: error: tilelayer type not found.");

   layer_num_columns = tilelayer["width"];
   layer_num_rows = tilelayer["height"];
   layer_tile_data = tilelayer["data"].get<std::vector<int>>();



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


   loaded = true;

   i.close();

   return true;
}

bool TMJDataLoader::file_exists(std::string filename)
{
   return std::filesystem::exists(filename);
}


} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


