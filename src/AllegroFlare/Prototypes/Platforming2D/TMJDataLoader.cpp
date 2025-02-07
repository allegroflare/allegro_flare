

#include <AllegroFlare/Prototypes/Platforming2D/TMJDataLoader.hpp>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/StringFormatValidator.hpp>
#include <AllegroFlare/Tiled/TMJDataLoader.hpp>
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
   , foreground_tilelayer_exists(false)
   , foreground_tilelayer_num_columns(0)
   , foreground_tilelayer_num_rows(0)
   , foreground_tilelayer_tile_data({})
   , background_tilelayer_exists(false)
   , background_tilelayer_num_columns(0)
   , background_tilelayer_num_rows(0)
   , background_tilelayer_tile_data({})
   , collision_layer_num_columns(0)
   , collision_layer_num_rows(0)
   , collision_layer_tile_data({})
   , background_color(DEFAULT_BACKGROUND_COLOR)
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
      error_message << "[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_num_columns]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_num_columns]: error: guard \"loaded\" not met");
   }
   return num_columns;
}

int TMJDataLoader::get_num_rows()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_num_rows]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_num_rows]: error: guard \"loaded\" not met");
   }
   return num_rows;
}

int TMJDataLoader::get_tile_width()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_tile_width]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_tile_width]: error: guard \"loaded\" not met");
   }
   return tile_width;
}

int TMJDataLoader::get_tile_height()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_tile_height]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_tile_height]: error: guard \"loaded\" not met");
   }
   return tile_height;
}

int TMJDataLoader::get_layer_num_columns()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_layer_num_columns]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_layer_num_columns]: error: guard \"loaded\" not met");
   }
   return layer_num_columns;
}

int TMJDataLoader::get_layer_num_rows()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_layer_num_rows]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_layer_num_rows]: error: guard \"loaded\" not met");
   }
   return layer_num_rows;
}

std::vector<int> TMJDataLoader::get_layer_tile_data()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_layer_tile_data]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_layer_tile_data]: error: guard \"loaded\" not met");
   }
   return layer_tile_data;
}

bool TMJDataLoader::get_foreground_tilelayer_exists()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_foreground_tilelayer_exists]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_foreground_tilelayer_exists]: error: guard \"loaded\" not met");
   }
   return foreground_tilelayer_exists;
}

int TMJDataLoader::get_foreground_tilelayer_num_columns()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_foreground_tilelayer_num_columns]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_foreground_tilelayer_num_columns]: error: guard \"loaded\" not met");
   }
   return foreground_tilelayer_num_columns;
}

int TMJDataLoader::get_foreground_tilelayer_num_rows()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_foreground_tilelayer_num_rows]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_foreground_tilelayer_num_rows]: error: guard \"loaded\" not met");
   }
   return foreground_tilelayer_num_rows;
}

std::vector<int> TMJDataLoader::get_foreground_tilelayer_tile_data()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_foreground_tilelayer_tile_data]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_foreground_tilelayer_tile_data]: error: guard \"loaded\" not met");
   }
   return foreground_tilelayer_tile_data;
}

bool TMJDataLoader::get_background_tilelayer_exists()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_background_tilelayer_exists]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_background_tilelayer_exists]: error: guard \"loaded\" not met");
   }
   return background_tilelayer_exists;
}

int TMJDataLoader::get_background_tilelayer_num_columns()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_background_tilelayer_num_columns]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_background_tilelayer_num_columns]: error: guard \"loaded\" not met");
   }
   return background_tilelayer_num_columns;
}

int TMJDataLoader::get_background_tilelayer_num_rows()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_background_tilelayer_num_rows]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_background_tilelayer_num_rows]: error: guard \"loaded\" not met");
   }
   return background_tilelayer_num_rows;
}

std::vector<int> TMJDataLoader::get_background_tilelayer_tile_data()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_background_tilelayer_tile_data]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_background_tilelayer_tile_data]: error: guard \"loaded\" not met");
   }
   return background_tilelayer_tile_data;
}

int TMJDataLoader::get_collision_layer_num_columns()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_collision_layer_num_columns]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_collision_layer_num_columns]: error: guard \"loaded\" not met");
   }
   return collision_layer_num_columns;
}

int TMJDataLoader::get_collision_layer_num_rows()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_collision_layer_num_rows]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_collision_layer_num_rows]: error: guard \"loaded\" not met");
   }
   return collision_layer_num_rows;
}

std::vector<int> TMJDataLoader::get_collision_layer_tile_data()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_collision_layer_tile_data]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_collision_layer_tile_data]: error: guard \"loaded\" not met");
   }
   return collision_layer_tile_data;
}

ALLEGRO_COLOR TMJDataLoader::get_background_color()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_background_color]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::get_background_color]: error: guard \"loaded\" not met");
   }
   return background_color;
}

bool TMJDataLoader::load()
{
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load]: error: guard \"(!loaded)\" not met");
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


   // Extract out the background color
   if (!j.contains("backgroundcolor"))
   {
      // TODO: Test this throw
      AllegroFlare::Logger::warn_from(
         "AllegroFlare::Tiled::TMJDataLoader::load",
         "Looking for \"backgroundcolor\" when loading \"" + filename + "\" but it does not exist. Using "
            "AllegroFlare::Tiled::TMJDataLoader::DEFAULT_BACKGROUND_COLOR instead."
      );
      background_color = DEFAULT_BACKGROUND_COLOR;
   }
   else
   {
      std::string background_color_as_hex_string = j["backgroundcolor"].get<std::string>();
      std::tuple<float, float, float, float> extracted_rgba_f =
         AllegroFlare::Tiled::TMJDataLoader::convert_hex_to_rgba_f(background_color_as_hex_string);
      background_color.r = std::get<0>(extracted_rgba_f);
      background_color.g = std::get<1>(extracted_rgba_f);
      background_color.b = std::get<2>(extracted_rgba_f);
      background_color.a = 1.0f; // NOTE: Alpha here will always be defaulted to 1.0

      //text__opacity = std::get<3>(extracted_rgba_f);
   }
   // HERE: Parse the background color
   //tile_height = j["tileheight"]; // get height


   //
   // Terrain tile layer
   //

   bool terrain_tilelayer_type_found = false;
   nlohmann::json terrain_tilelayer; // TODO: Rename this "terrain_tilelayer"

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

      terrain_tilelayer = layer.value();
      terrain_tilelayer_type_found = true;
      AllegroFlare::Logger::info_from(
         "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
         "Found layer \"" + layer_name + "\" to use as visual tile layer."
      );
      break;
   }

   // If no "terrain" layer was found of type "tilelayer", look for the first "tilelayer" that does not have
   // excluding features.
   if (!terrain_tilelayer_type_found)
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
         //if (layer.value()["name"] == "collision") continue;
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

         terrain_tilelayer = layer.value();
         terrain_tilelayer_type_found = true;
         AllegroFlare::Logger::info_from(
            "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
            "Found layer \"" + layer_name + "\" to use as visual tile layer."
         );
         break;
      }
   }


   // Throw if an appropriate tilelayer was never found
   if (!terrain_tilelayer_type_found)
   {
      throw std::runtime_error("TMJMeshLoader: error: tilelayer for visual tiles was not found.");
   }


   // Look for the "terrain_manual_override" tilelayer
   bool terrain_manual_override_tilelayer_type_found = false;
   nlohmann::json terrain_manual_override_tilelayer;
   // First, look for a tilelayer type named "terrain"
   // TODO: Test this behavior
   for (auto &layer : j["layers"].items())
   {
      std::string layer_name = layer.value()["name"];

      if (layer_name != "terrain_manual_override") continue;

      if (layer.value()["type"] != "tilelayer")
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
            "Found a layer named \"terrain_manual_override\" but it was expected to be a \"tilelayer\" type "
               "layer and was not."
         );
      }

      terrain_manual_override_tilelayer = layer.value();
      terrain_manual_override_tilelayer_type_found = true;
      AllegroFlare::Logger::info_from(
         "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
         "Found layer \"" + layer_name + "\" to use as override when compositing the visual tile layer."
      );
      break;
   }


   // Terrain manual override

   // If the "terrain_manual_override" tilelayer exists, override the tiles in the "terrain"
   // TODO: Test this feature
   layer_num_columns = terrain_tilelayer["width"];
   layer_num_rows = terrain_tilelayer["height"];
   layer_tile_data = terrain_tilelayer["data"].get<std::vector<int>>();

   if (terrain_manual_override_tilelayer_type_found)
   {
      int override_num_columns = terrain_manual_override_tilelayer["width"];
      int override_num_rows = terrain_manual_override_tilelayer["height"];

      std::vector<int> override_tile_data = terrain_manual_override_tilelayer["data"].get<std::vector<int>>();

      if (override_num_columns != layer_num_columns)
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
            "asdfasdfasdfas45783"
         );
      }
      if (override_num_rows != layer_num_rows)
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
            "983479jsaopdfjiaodf"
         );
      }
      if (override_tile_data.size() != layer_tile_data.size())
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
            "aa7agy0ayg0ad0a"
         );
      }

      AllegroFlare::Logger::info_from(
         "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
         "Overriding \"terrain\" layer with non-zero tiles of \"terrain_manual_override\" layer."
      );
      int override_count = 0;
      for (int i=0; i<override_tile_data.size(); i++)
      {
         if (override_tile_data[i] != 0)
         {
            //std::cout << ".";
            override_count++;
            layer_tile_data[i] = override_tile_data[i];
         }
      }
      AllegroFlare::Logger::info_from(
         "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
         std::to_string(override_count) + " tiles overridden."
      );
   }



   //
   // Background tile layer
   //

   //background_tilelayer_found = false;
   nlohmann::json background_tilelayer;

   // TODO: Test this behavior
   for (auto &layer : j["layers"].items())
   {
      std::string layer_name = layer.value()["name"];

      if (layer_name != "background") continue;

      if (layer.value()["type"] != "tilelayer")
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
            "Found a layer named \"background\" but it was expected to be a \"tilelayer\" type layer and was not."
         );
      }

      background_tilelayer = layer.value();
      background_tilelayer_exists = true;
      AllegroFlare::Logger::info_from(
         "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
         "Found layer \"" + layer_name + "\" to use as background tile layer."
      );
      break;
   }

   if (!background_tilelayer_exists)
   {
      AllegroFlare::Logger::warn_from( // Consider if this should be info, warn, or throw, depending on the user
         "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
         "Layer named \"background\" was not found. Skipping."
      );
   }
   else
   {
      background_tilelayer_num_columns = background_tilelayer["width"];
      background_tilelayer_num_rows = background_tilelayer["height"];
      background_tilelayer_tile_data = background_tilelayer["data"].get<std::vector<int>>();
   }


   // Background manual override

   // Look for the "background_manual_override" tilelayer
   bool background_manual_override_tilelayer_type_found = false;
   nlohmann::json background_manual_override_tilelayer;
   // First, look for a tilelayer type named "background_manual_override"
   // TODO: Test this behavior
   for (auto &layer : j["layers"].items())
   {
      std::string layer_name = layer.value()["name"];

      if (layer_name != "background_manual_override") continue;

      if (layer.value()["type"] != "tilelayer")
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
            "Found a layer named \"background_manual_override\" but it was expected to be a \"tilelayer\" type "
               "layer and was not."
         );
      }

      background_manual_override_tilelayer = layer.value();
      background_manual_override_tilelayer_type_found = true;
      AllegroFlare::Logger::info_from(
         "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
         "Found layer \"" + layer_name + "\" to use as override when compositing the visual tile layer."
      );
      break;
   }


   // If the "background_manual_override" tilelayer exists, override the tiles in the "background"
   // TODO: Test this feature
   //layer_num_columns = background_tilelayer["width"];
   //layer_num_rows = background_tilelayer["height"];
   //layer_tile_data = background_tilelayer["data"].get<std::vector<int>>();

   if (background_manual_override_tilelayer_type_found)
   {
      int override_num_columns = background_manual_override_tilelayer["width"];
      int override_num_rows = background_manual_override_tilelayer["height"];

      std::vector<int> override_tile_data = background_manual_override_tilelayer["data"].get<std::vector<int>>();

      if (override_num_columns != background_tilelayer_num_columns)
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
            "ztioztioiziu0gzgiu"
         );
      }
      if (override_num_rows != background_tilelayer_num_rows)
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
            "qhw,.erhq,.rw.hkqrw"
         );
      }
      if (override_tile_data.size() != background_tilelayer_tile_data.size())
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
            "rqytwertueqwruety"
         );
      }

      AllegroFlare::Logger::info_from(
         "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
         "Overriding \"background\" layer with non-zero tiles of \"background_manual_override\" layer."
      );
      int override_count = 0;
      for (int i=0; i<override_tile_data.size(); i++)
      {
         if (override_tile_data[i] != 0)
         {
            //std::cout << ".";
            override_count++;
            background_tilelayer_tile_data[i] = override_tile_data[i];
         }
      }
      AllegroFlare::Logger::info_from(
         "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
         std::to_string(override_count) + " tiles overridden in background."
      );
   }







   //
   // Foreground tile layer
   //

   // TODO: Test loading of foreground tile layer
   // TODO: Test loading and overriding of "foreground_manual_override"

   //foreground_tilelayer_found = false;
   nlohmann::json foreground_tilelayer;

   // TODO: Test this behavior
   for (auto &layer : j["layers"].items())
   {
      std::string layer_name = layer.value()["name"];

      if (layer_name != "foreground") continue;

      if (layer.value()["type"] != "tilelayer")
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
            "Found a layer named \"foreground\" but it was expected to be a \"tilelayer\" type layer and was not."
         );
      }

      foreground_tilelayer = layer.value();
      foreground_tilelayer_exists = true;
      AllegroFlare::Logger::info_from(
         "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
         "Found layer \"" + layer_name + "\" to use as foreground tile layer."
      );
      break;
   }

   if (!foreground_tilelayer_exists)
   {
      AllegroFlare::Logger::warn_from( // Consider if this should be info, warn, or throw, depending on the user
         "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
         "Layer named \"foreground\" was not found. Skipping."
      );
   }
   else
   {
      foreground_tilelayer_num_columns = foreground_tilelayer["width"];
      foreground_tilelayer_num_rows = foreground_tilelayer["height"];
      foreground_tilelayer_tile_data = foreground_tilelayer["data"].get<std::vector<int>>();
   }


   // Foreground manual override

   // Look for the "foreground_manual_override" tilelayer
   bool foreground_manual_override_tilelayer_type_found = false;
   nlohmann::json foreground_manual_override_tilelayer;
   // First, look for a tilelayer type named "foreground_manual_override"
   // TODO: Test this behavior
   for (auto &layer : j["layers"].items())
   {
      std::string layer_name = layer.value()["name"];

      if (layer_name != "foreground_manual_override") continue;

      if (layer.value()["type"] != "tilelayer")
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
            "Found a layer named \"foreground_manual_override\" but it was expected to be a \"tilelayer\" type "
               "layer and was not."
         );
      }

      foreground_manual_override_tilelayer = layer.value();
      foreground_manual_override_tilelayer_type_found = true;
      AllegroFlare::Logger::info_from(
         "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
         "Found layer \"" + layer_name + "\" to use as override when compositing the visual tile layer."
      );
      break;
   }


   // If the "foreground_manual_override" tilelayer exists, override the tiles in the "foreground"
   // TODO: Test this feature
   //layer_num_columns = foreground_tilelayer["width"];
   //layer_num_rows = foreground_tilelayer["height"];
   //layer_tile_data = foreground_tilelayer["data"].get<std::vector<int>>();

   if (foreground_manual_override_tilelayer_type_found)
   {
      int override_num_columns = foreground_manual_override_tilelayer["width"];
      int override_num_rows = foreground_manual_override_tilelayer["height"];

      std::vector<int> override_tile_data = foreground_manual_override_tilelayer["data"].get<std::vector<int>>();

      if (override_num_columns != foreground_tilelayer_num_columns)
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
            "ztioztioiziu0gzgiu"
         );
      }
      if (override_num_rows != foreground_tilelayer_num_rows)
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
            "qhw,.erhq,.rw.hkqrw"
         );
      }
      if (override_tile_data.size() != foreground_tilelayer_tile_data.size())
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
            "rqytwertueqwruety"
         );
      }

      AllegroFlare::Logger::info_from(
         "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
         "Overriding \"foreground\" layer with non-zero tiles of \"foreground_manual_override\" layer."
      );
      int override_count = 0;
      for (int i=0; i<override_tile_data.size(); i++)
      {
         if (override_tile_data[i] != 0)
         {
            //std::cout << ".";
            override_count++;
            foreground_tilelayer_tile_data[i] = override_tile_data[i];
         }
      }
      AllegroFlare::Logger::info_from(
         "AllegroFlare::Prototypes::Platforming2D::TMJDataLoader::load",
         std::to_string(override_count) + " tiles overridden in foreground."
      );
   }







   // Throw if an appropriate tilelayer was never found
   //if (!tilelayer_type_found)
   //{
      //throw std::runtime_error("TMJMeshLoader: error: tilelayer for visual tiles was not found.");
   //}

   //layer_num_columns = tilelayer["width"];
   //layer_num_rows = tilelayer["height"];
   //layer_tile_data = tilelayer["data"].get<std::vector<int>>();
   if (normalize_tile_data_from_tilesets)
   {
      // TODO: Test this normalization is correct with multiple tilesets
      layer_tile_data = normalize_tile_data_to_tilesets_firstgids(
            layer_tile_data,
            tilesets_gids
         );

      background_tilelayer_tile_data = normalize_tile_data_to_tilesets_firstgids(
            background_tilelayer_tile_data,
            tilesets_gids
         );

      foreground_tilelayer_tile_data = normalize_tile_data_to_tilesets_firstgids(
            foreground_tilelayer_tile_data,
            tilesets_gids
         );
   }



   //
   // Collision tile layer
   //

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


