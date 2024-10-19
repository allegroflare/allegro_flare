

#include <AllegroFlare/TileMaps/TileAtlasRepository.hpp>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/TileMaps/TileAtlasBuilder.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace TileMaps
{


TileAtlasRepository::TileAtlasRepository()
   : tile_atlas_bitmap_bin()
   , data_path(DEFAULT_DATA_PATH)
   , asset_subdirectory(DEFAULT_ASSET_SUBDIRECTORY)
   , repository()
   , initialized(false)
{
}


TileAtlasRepository::~TileAtlasRepository()
{
}


void TileAtlasRepository::set_data_path(std::string data_path)
{
   if (get_initialized()) throw std::runtime_error("[TileAtlasRepository::set_data_path]: error: guard \"get_initialized()\" not met.");
   this->data_path = data_path;
}


void TileAtlasRepository::set_asset_subdirectory(std::string asset_subdirectory)
{
   if (get_initialized()) throw std::runtime_error("[TileAtlasRepository::set_asset_subdirectory]: error: guard \"get_initialized()\" not met.");
   this->asset_subdirectory = asset_subdirectory;
}


std::string TileAtlasRepository::get_data_path() const
{
   return data_path;
}


std::string TileAtlasRepository::get_asset_subdirectory() const
{
   return asset_subdirectory;
}


bool TileAtlasRepository::get_initialized() const
{
   return initialized;
}


void TileAtlasRepository::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::TileAtlasRepository::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::TileAtlasRepository::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!((data_path != DEFAULT_DATA_PATH)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::TileAtlasRepository::initialize]: error: guard \"(data_path != DEFAULT_DATA_PATH)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::TileAtlasRepository::initialize]: error: guard \"(data_path != DEFAULT_DATA_PATH)\" not met");
   }
   tile_atlas_bitmap_bin.set_path(data_path + asset_subdirectory); // NOTE: Will implicitly init when setting path
   initialized = true;
   return;
}

AllegroFlare::TileMaps::PrimMeshAtlas* TileAtlasRepository::fetch(std::string identifier)
{
   auto it = repository.find(identifier);
   if (it == repository.end())
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileAtlasRepository::fetch",
         "A tile atlas with the identifier \"" + identifier + "\" does not exist."
      );
   }
   return &it->second.tile_atlas;
}

bool TileAtlasRepository::exists(std::string identifier)
{
   auto it = repository.find(identifier);
   if (it == repository.end()) return false;
   return true;
}

void TileAtlasRepository::destroy(std::string identifier)
{
   AllegroFlare::Logger::warn_from_once(
      "AllegroFlare::TileMaps::TileAtlasRepository::destroy",
      "This feature is not yet implemented. Feel free to add it!"
   );
}

void TileAtlasRepository::load(std::string identifier, std::string source_bitmap_filename, int source_bitmap_tile_width, int source_bitmap_tile_height, int scale)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::TileAtlasRepository::load]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::TileAtlasRepository::load]: error: guard \"initialized\" not met");
   }
   if (exists(identifier))
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::TileMaps::TileAtlasRepository::load",
         "A tile atlas with the identifier \"" + identifier + "\" already exists."
      );
   }

   // Preload the inital source bitmap through the bin
   tile_atlas_bitmap_bin.load(source_bitmap_filename, source_bitmap_filename, "TileAtlasRepository::load");

   // Obtain the inital source bitmap
   ALLEGRO_BITMAP *initial_source_bitmap = tile_atlas_bitmap_bin.auto_get(source_bitmap_filename);

   // Assemble the bitmap (duplicate the source bitmap at scale)
   ALLEGRO_BITMAP *scaled_extruded_tile_map_bitmap =
      AllegroFlare::TileMaps::TileAtlasBuilder::create_scaled_and_extruded(initial_source_bitmap, scale);

   // Add a record to the repository for this tile_atlas
   repository[identifier] = AllegroFlare::TileMaps::TileAtlasRepositoryRecord();

   // Load the image into the tile atlas, having the TileAtlas create a copy of the bitmap for itself
   fetch(identifier)->duplicate_bitmap_and_load(
      scaled_extruded_tile_map_bitmap,
      source_bitmap_tile_width*scale,
      source_bitmap_tile_height*scale,
      1
   );

   // Destroy the duplicate scaled extruded bitmap
   al_destroy_bitmap(scaled_extruded_tile_map_bitmap);

   // Destroy the bitmap that was loaded through our local tile_atlas_bitmap_bin, and remove its record from the bin
   tile_atlas_bitmap_bin.destroy(source_bitmap_filename);

   return;
}


} // namespace TileMaps
} // namespace AllegroFlare


