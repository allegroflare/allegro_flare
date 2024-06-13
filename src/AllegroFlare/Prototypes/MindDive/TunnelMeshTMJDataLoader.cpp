

#include <AllegroFlare/Prototypes/MindDive/TunnelMeshTMJDataLoader.hpp>

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
namespace MindDive
{


TunnelMeshTMJDataLoader::TunnelMeshTMJDataLoader(std::string filename)
   : filename(filename)
   , num_columns(0)
   , num_rows(0)
   , tile_width(0)
   , tile_height(0)
   , layer_num_columns(0)
   , layer_num_rows(0)
   , layer_tile_data({})
   , loaded(false)
{
}


TunnelMeshTMJDataLoader::~TunnelMeshTMJDataLoader()
{
}


bool TunnelMeshTMJDataLoader::get_loaded() const
{
   return loaded;
}


int TunnelMeshTMJDataLoader::get_num_columns()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader::get_num_columns]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader::get_num_columns]: error: guard \"loaded\" not met");
   }
   return num_columns;
}

int TunnelMeshTMJDataLoader::get_num_rows()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader::get_num_rows]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader::get_num_rows]: error: guard \"loaded\" not met");
   }
   return num_rows;
}

int TunnelMeshTMJDataLoader::get_tile_width()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader::get_tile_width]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader::get_tile_width]: error: guard \"loaded\" not met");
   }
   return tile_width;
}

int TunnelMeshTMJDataLoader::get_tile_height()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader::get_tile_height]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader::get_tile_height]: error: guard \"loaded\" not met");
   }
   return tile_height;
}

int TunnelMeshTMJDataLoader::get_layer_num_columns()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader::get_layer_num_columns]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader::get_layer_num_columns]: error: guard \"loaded\" not met");
   }
   return layer_num_columns;
}

int TunnelMeshTMJDataLoader::get_layer_num_rows()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader::get_layer_num_rows]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader::get_layer_num_rows]: error: guard \"loaded\" not met");
   }
   return layer_num_rows;
}

std::vector<int> TunnelMeshTMJDataLoader::get_layer_tile_data()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader::get_layer_tile_data]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader::get_layer_tile_data]: error: guard \"loaded\" not met");
   }
   return layer_tile_data;
}

bool TunnelMeshTMJDataLoader::load()
{
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader::load]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::TunnelMeshTMJDataLoader::load]: error: guard \"(!loaded)\" not met");
   }
   if (!file_exists(filename))
   {
      std::stringstream error_message;
      error_message << "[MindDive::TunnelMeshTMJDataLoader] load() error: the file \""
                    << filename << "\" does not exist.";
      throw std::runtime_error(error_message.str());
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
      error_message << "[MindDive::TunnelMeshTMJDataLoader] load() error: the file \""
                    << filename << "\" appears to have"
                    << " malformed JSON. The following error was thrown by nlohmann::json: \""
                    << e.what() << "\"";
      throw std::runtime_error(error_message.str());
   }

   num_columns = j["width"]; // get width
   num_rows = j["height"]; // get height
   tile_width = j["tilewidth"]; // get width
   tile_height = j["tileheight"]; // get height

   // get first j["layers"] that is a ["type"] == "tilelayer"
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

   loaded = true;

   i.close();

   return true;
}

bool TunnelMeshTMJDataLoader::file_exists(std::string filename)
{
   return std::filesystem::exists(filename);
}


} // namespace MindDive
} // namespace Prototypes
} // namespace AllegroFlare


