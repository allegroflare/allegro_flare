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
         class TMJTileMeshLoader
         {
         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            std::string tmj_filename;
            std::string tile_atlas_bitmap_identifier;
            int tile_atlas_tile_width;
            int tile_atlas_tile_height;
            AllegroFlare::TileMaps::PrimMeshAtlas* tile_atlas;
            AllegroFlare::TileMaps::PrimMesh* terrain_mesh;
            AllegroFlare::TileMaps::PrimMesh* background_mesh;
            AllegroFlare::TileMaps::PrimMesh* foreground_mesh;
            AllegroFlare::TileMaps::TileMap<int>* collision_tile_map;
            bool loaded;

         protected:


         public:
            TMJTileMeshLoader(AllegroFlare::BitmapBin* bitmap_bin=nullptr, std::string tmj_filename="[unset-tmj_filename]", std::string tile_atlas_bitmap_identifier="[unset-tile_atlas_bitmap_identifier]", int tile_atlas_tile_width=16, int tile_atlas_tile_height=16);
            ~TMJTileMeshLoader();

            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            std::string get_tmj_filename() const;
            std::string get_tile_atlas_bitmap_identifier() const;
            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
            void set_tmj_filename(std::string tmj_filename="[unset-tmj_filename]");
            void set_tile_atlas_bitmap_identifier(std::string tile_atlas_bitmap_identifier="[unset-tile_atlas_bitmap_identifier]");
            AllegroFlare::TileMaps::PrimMeshAtlas* get_tile_atlas();
            AllegroFlare::TileMaps::PrimMesh* get_terrain_mesh();
            AllegroFlare::TileMaps::PrimMesh* get_background_mesh();
            AllegroFlare::TileMaps::PrimMesh* get_foreground_mesh();
            AllegroFlare::TileMaps::TileMap<int>* get_collision_tile_map();
            bool load();
         };
      }
   }
}



