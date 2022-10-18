#pragma once


#include <AllegroFlare/Prototypes/TileDrive/TerrainMesh.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace TileDrive
      {
         class TerrainMeshDictionaryRecord
         {
         private:
            std::string tmj_filename;
            std::string tile_atlas_bitmap_identifier;
            int tile_atlas_tile_width;
            int tile_atlas_tile_height;
            AllegroFlare::Prototypes::TileDrive::TerrainMesh* terrain_mesh;

         protected:


         public:
            TerrainMeshDictionaryRecord(std::string tmj_filename="[unset-tmj_filename]", std::string tile_atlas_bitmap_identifier="[unset-tile_atlas_bitmap_identifier]", int tile_atlas_tile_width=1, int tile_atlas_tile_height=1, AllegroFlare::Prototypes::TileDrive::TerrainMesh* terrain_mesh=nullptr);
            ~TerrainMeshDictionaryRecord();

            void set_tmj_filename(std::string tmj_filename);
            void set_tile_atlas_bitmap_identifier(std::string tile_atlas_bitmap_identifier);
            void set_tile_atlas_tile_width(int tile_atlas_tile_width);
            void set_tile_atlas_tile_height(int tile_atlas_tile_height);
            void set_terrain_mesh(AllegroFlare::Prototypes::TileDrive::TerrainMesh* terrain_mesh);
            std::string get_tmj_filename() const;
            std::string get_tile_atlas_bitmap_identifier() const;
            int get_tile_atlas_tile_width() const;
            int get_tile_atlas_tile_height() const;
            AllegroFlare::Prototypes::TileDrive::TerrainMesh* get_terrain_mesh() const;
            AllegroFlare::Prototypes::TileDrive::TerrainMesh* &get_terrain_mesh_ref();
         };
      }
   }
}



