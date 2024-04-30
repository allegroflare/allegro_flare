#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>
#include <AllegroFlare/TileMaps/TileAtlasRepositoryRecord.hpp>
#include <map>
#include <string>


namespace AllegroFlare
{
   namespace TileMaps
   {
      class TileAtlasRepository
      {
      public:
         static constexpr char* DEFAULT_DATA_PATH = (char*)"[unset-data_path]";
         static constexpr char* DEFAULT_ASSET_SUBDIRECTORY = (char*)"bitmaps";

      private:
         AllegroFlare::BitmapBin tile_atlas_bitmap_bin;
         std::string data_path;
         std::string asset_subdirectory;
         std::map<std::string, AllegroFlare::TileMaps::TileAtlasRepositoryRecord> repository;
         bool initialized;

      protected:


      public:
         TileAtlasRepository();
         ~TileAtlasRepository();

         void set_data_path(std::string data_path);
         void set_asset_subdirectory(std::string asset_subdirectory);
         std::string get_data_path() const;
         std::string get_asset_subdirectory() const;
         bool get_initialized() const;
         void initialize();
         AllegroFlare::TileMaps::PrimMeshAtlas* fetch(std::string identifier="[unset-identifier]");
         bool exists(std::string identifier="[unset-identifier]");
         void destroy(std::string identifier="[unset-identifier]");
         void load(std::string identifier="[unset-identifier]", std::string source_bitmap_filename="[unset-source_bitmap_filename]", int source_bitmap_tile_width=16, int source_bitmap_tile_height=16, int scale=3);
      };
   }
}



