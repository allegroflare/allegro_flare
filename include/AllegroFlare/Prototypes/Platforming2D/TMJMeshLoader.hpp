#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/TileMaps/PrimMesh.hpp>
#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>
#include <AllegroFlare/TileMaps/TileMap.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Platforming2D
      {
         class TMJMeshLoader
         {
         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            std::string tmj_filename;
            std::string bitmap_atlas_filename;
            AllegroFlare::TileMaps::PrimMeshAtlas* tile_atlas;
            AllegroFlare::TileMaps::PrimMesh* mesh;
            AllegroFlare::TileMaps::TileMap<int>* collision_tile_map;
            bool loaded;

         protected:


         public:
            TMJMeshLoader(AllegroFlare::BitmapBin* bitmap_bin=nullptr, std::string tmj_filename="filename-not-set.tmj", std::string bitmap_atlas_filename="tiles_dungeon_v1.1.png");
            ~TMJMeshLoader();

            AllegroFlare::TileMaps::PrimMeshAtlas* get_tile_atlas();
            AllegroFlare::TileMaps::PrimMesh* get_mesh();
            AllegroFlare::TileMaps::TileMap<int>* get_collision_tile_map();
            bool load();
         };
      }
   }
}



