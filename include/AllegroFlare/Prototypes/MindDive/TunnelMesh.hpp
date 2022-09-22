#pragma once


#include <AllegroFlare/BitmapBin.hpp>
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
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::TileMaps::PrimMeshAtlas atlas;
            AllegroFlare::TileMaps::PrimMesh prim_mesh;
            AllegroFlare::TileMaps::TileMap<int> collision_tile_map;
            bool initialized;

         protected:


         public:
            TunnelMesh(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
            ~TunnelMesh();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::TileMaps::PrimMeshAtlas &get_atlas_ref();
            AllegroFlare::TileMaps::PrimMesh &get_prim_mesh_ref();
            AllegroFlare::TileMaps::TileMap<int> &get_collision_tile_map_ref();
            void initialize();
            float infer_real_width();
            float infer_real_height();
            void render();
         };
      }
   }
}



