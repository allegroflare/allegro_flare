#pragma once


#include <AllegroFlare/Elements/Backgrounds/ParallaxLayer.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2D.hpp>
#include <AllegroFlare/Shaders/Base.hpp>
#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>
#include <AllegroFlare/TileMaps/TileMap.hpp>
#include <AllegroFlare/TileMaps/TileMesh.hpp>
#include <vector>


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
                  AllegroFlare::TileMaps::TileMesh* terrain_tile_mesh;
                  AllegroFlare::Shaders::Base* shader_for_terrain_tile_mesh;
                  AllegroFlare::TileMaps::TileMesh* background_tile_mesh;
                  AllegroFlare::Shaders::Base* shader_for_background_tile_mesh;
                  AllegroFlare::TileMaps::TileMesh* foreground_tile_mesh;
                  AllegroFlare::Shaders::Base* shader_for_foreground_tile_mesh;
                  AllegroFlare::TileMaps::TileMap<int>* collision_tile_map;
                  std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> background_layers;

               protected:


               public:
                  Basic2D(std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> background_layers={});
                  virtual ~Basic2D();

                  void set_tile_atlas(AllegroFlare::TileMaps::PrimMeshAtlas* tile_atlas);
                  void set_terrain_tile_mesh(AllegroFlare::TileMaps::TileMesh* terrain_tile_mesh);
                  void set_shader_for_terrain_tile_mesh(AllegroFlare::Shaders::Base* shader_for_terrain_tile_mesh);
                  void set_background_tile_mesh(AllegroFlare::TileMaps::TileMesh* background_tile_mesh);
                  void set_shader_for_background_tile_mesh(AllegroFlare::Shaders::Base* shader_for_background_tile_mesh);
                  void set_foreground_tile_mesh(AllegroFlare::TileMaps::TileMesh* foreground_tile_mesh);
                  void set_shader_for_foreground_tile_mesh(AllegroFlare::Shaders::Base* shader_for_foreground_tile_mesh);
                  void set_collision_tile_map(AllegroFlare::TileMaps::TileMap<int>* collision_tile_map);
                  void set_background_layers(std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> background_layers);
                  AllegroFlare::TileMaps::PrimMeshAtlas* get_tile_atlas() const;
                  AllegroFlare::TileMaps::TileMesh* get_terrain_tile_mesh() const;
                  AllegroFlare::Shaders::Base* get_shader_for_terrain_tile_mesh() const;
                  AllegroFlare::TileMaps::TileMesh* get_background_tile_mesh() const;
                  AllegroFlare::Shaders::Base* get_shader_for_background_tile_mesh() const;
                  AllegroFlare::TileMaps::TileMesh* get_foreground_tile_mesh() const;
                  AllegroFlare::Shaders::Base* get_shader_for_foreground_tile_mesh() const;
                  AllegroFlare::TileMaps::TileMap<int>* get_collision_tile_map() const;
                  std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> get_background_layers() const;
                  virtual void update() override;
                  virtual void draw() override;
                  virtual void destroy() override;
               };
            }
         }
      }
   }
}



