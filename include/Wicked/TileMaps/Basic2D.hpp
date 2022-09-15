#pragma once


#include <Tileo/Atlas.hpp>
#include <Tileo/Mesh.hpp>
#include <Tileo/TileMap.hpp>
#include <Wicked/TileMaps/Base.hpp>


namespace Wicked
{
   namespace TileMaps
   {
      class Basic2D : public Wicked::TileMaps::Base
      {
      private:
         Tileo::Atlas* tile_atlas;
         Tileo::Mesh* tile_mesh;
         Tileo::TileMap* collision_tile_mesh;

      protected:


      public:
         Basic2D();
         ~Basic2D();

         void set_tile_atlas(Tileo::Atlas* tile_atlas);
         void set_tile_mesh(Tileo::Mesh* tile_mesh);
         void set_collision_tile_mesh(Tileo::TileMap* collision_tile_mesh);
         Tileo::Atlas* get_tile_atlas() const;
         Tileo::Mesh* get_tile_mesh() const;
         Tileo::TileMap* get_collision_tile_mesh() const;
      };
   }
}



