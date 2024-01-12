#pragma once


#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2D.hpp>
#include <AllegroFlare/TileMaps/PrimMesh.hpp>
#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>
#include <AllegroFlare/TileMaps/TileMap.hpp>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Platforming2D
      {
         namespace Entities
         {
            namespace TileMaps
            {
               class Basic2D : public AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D
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
                  void destroy();
               };
            }
         }
      }
   }
}



