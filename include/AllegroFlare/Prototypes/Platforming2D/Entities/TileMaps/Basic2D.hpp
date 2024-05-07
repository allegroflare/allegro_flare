#pragma once


#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2D.hpp>
#include <AllegroFlare/Shaders/Base.hpp>
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
                  AllegroFlare::TileMaps::PrimMesh* terrain_tile_mesh;
                  AllegroFlare::Shaders::Base* shader_for_terrain_tile_mesh;
                  AllegroFlare::TileMaps::PrimMesh* background_tile_mesh;
                  AllegroFlare::Shaders::Base* shader_for_background_tile_mesh;
                  AllegroFlare::TileMaps::PrimMesh* foreground_tile_mesh;
                  AllegroFlare::Shaders::Base* shader_for_foreground_tile_mesh;
                  AllegroFlare::TileMaps::TileMap<int>* collision_tile_mesh;

               protected:


               public:
                  Basic2D();
                  virtual ~Basic2D();

                  void set_tile_atlas(AllegroFlare::TileMaps::PrimMeshAtlas* tile_atlas);
                  void set_terrain_tile_mesh(AllegroFlare::TileMaps::PrimMesh* terrain_tile_mesh);
                  void set_shader_for_terrain_tile_mesh(AllegroFlare::Shaders::Base* shader_for_terrain_tile_mesh);
                  void set_background_tile_mesh(AllegroFlare::TileMaps::PrimMesh* background_tile_mesh);
                  void set_shader_for_background_tile_mesh(AllegroFlare::Shaders::Base* shader_for_background_tile_mesh);
                  void set_foreground_tile_mesh(AllegroFlare::TileMaps::PrimMesh* foreground_tile_mesh);
                  void set_shader_for_foreground_tile_mesh(AllegroFlare::Shaders::Base* shader_for_foreground_tile_mesh);
                  void set_collision_tile_mesh(AllegroFlare::TileMaps::TileMap<int>* collision_tile_mesh);
                  AllegroFlare::TileMaps::PrimMeshAtlas* get_tile_atlas() const;
                  AllegroFlare::TileMaps::PrimMesh* get_terrain_tile_mesh() const;
                  AllegroFlare::Shaders::Base* get_shader_for_terrain_tile_mesh() const;
                  AllegroFlare::TileMaps::PrimMesh* get_background_tile_mesh() const;
                  AllegroFlare::Shaders::Base* get_shader_for_background_tile_mesh() const;
                  AllegroFlare::TileMaps::PrimMesh* get_foreground_tile_mesh() const;
                  AllegroFlare::Shaders::Base* get_shader_for_foreground_tile_mesh() const;
                  AllegroFlare::TileMaps::TileMap<int>* get_collision_tile_mesh() const;
                  virtual void update() override;
                  virtual void draw() override;
                  void destroy();
               };
            }
         }
      }
   }
}



