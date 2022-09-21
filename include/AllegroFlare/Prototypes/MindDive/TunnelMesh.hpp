#pragma once


#include <AllegroFlare/TileMaps/PrimMesh.hpp>
#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>
#include <AllegroFlare/TileMaps/TileMap.hpp>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace MindDive
      {
         class TunnelMesh
         {
         private:
            AllegroFlare::TileMaps::PrimMeshAtlas atlas;
            AllegroFlare::TileMaps::PrimMesh prim_mesh;
            AllegroFlare::TileMaps::TileMap<int> collision_tile_map;
            bool initialized;

         protected:


         public:
            TunnelMesh();
            ~TunnelMesh();

            AllegroFlare::TileMaps::PrimMeshAtlas &get_atlas_ref();
            AllegroFlare::TileMaps::PrimMesh &get_prim_mesh_ref();
            AllegroFlare::TileMaps::TileMap<int> &get_collision_tile_map_ref();
            void initialize();
            void render();
         };
      }
   }
}



