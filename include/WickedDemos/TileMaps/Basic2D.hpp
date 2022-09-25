#pragma once


#include <AllegroFlare/TileMaps/PrimMesh.hpp>
#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>
#include <AllegroFlare/TileMaps/TileMap.hpp>
#include <Wicked/Entities/Basic2D.hpp>


namespace WickedDemos
{
   namespace TileMaps
   {
      class Basic2D : public Wicked::Entities::Basic2D
      {
      private:
         AllegroFlare::TileMaps::PrimMeshAtlas* tile_atlas;
         AllegroFlare::TileMaps::PrimMesh* tile_mesh;
         AllegroFlare::TileMaps::TileMap<int>* collision_tile_mesh;

      protected:


      public:
         Basic2D();
         ~Basic2D();

         void set_tile_atlas(AllegroFlare::TileMaps::PrimMeshAtlas* tile_atlas);
         void set_tile_mesh(AllegroFlare::TileMaps::PrimMesh* tile_mesh);
         void set_collision_tile_mesh(AllegroFlare::TileMaps::TileMap<int>* collision_tile_mesh);
         AllegroFlare::TileMaps::PrimMeshAtlas* get_tile_atlas() const;
         AllegroFlare::TileMaps::PrimMesh* get_tile_mesh() const;
         AllegroFlare::TileMaps::TileMap<int>* get_collision_tile_mesh() const;
      };
   }
}



