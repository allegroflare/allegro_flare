

#include <AllegroFlare/Prototypes/Platforming2D/Entities/TileMaps/Basic2D.hpp>




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


Basic2D::Basic2D(std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> background_layers, std::vector<AllegroFlare::Elements::ImageLayer> image_layers)
   : AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D()
   , tile_atlas(nullptr)
   , terrain_tile_mesh(nullptr)
   , shader_for_terrain_tile_mesh(nullptr)
   , background_tile_mesh(nullptr)
   , shader_for_background_tile_mesh(nullptr)
   , foreground_tile_mesh(nullptr)
   , shader_for_foreground_tile_mesh(nullptr)
   , collision_tile_map(nullptr)
   , background_layers(background_layers)
   , image_layers(image_layers)
{
}


Basic2D::~Basic2D()
{
}


void Basic2D::set_tile_atlas(AllegroFlare::TileMaps::PrimMeshAtlas* tile_atlas)
{
   this->tile_atlas = tile_atlas;
}


void Basic2D::set_terrain_tile_mesh(AllegroFlare::TileMaps::TileMesh* terrain_tile_mesh)
{
   this->terrain_tile_mesh = terrain_tile_mesh;
}


void Basic2D::set_shader_for_terrain_tile_mesh(AllegroFlare::Shaders::Base* shader_for_terrain_tile_mesh)
{
   this->shader_for_terrain_tile_mesh = shader_for_terrain_tile_mesh;
}


void Basic2D::set_background_tile_mesh(AllegroFlare::TileMaps::TileMesh* background_tile_mesh)
{
   this->background_tile_mesh = background_tile_mesh;
}


void Basic2D::set_shader_for_background_tile_mesh(AllegroFlare::Shaders::Base* shader_for_background_tile_mesh)
{
   this->shader_for_background_tile_mesh = shader_for_background_tile_mesh;
}


void Basic2D::set_foreground_tile_mesh(AllegroFlare::TileMaps::TileMesh* foreground_tile_mesh)
{
   this->foreground_tile_mesh = foreground_tile_mesh;
}


void Basic2D::set_shader_for_foreground_tile_mesh(AllegroFlare::Shaders::Base* shader_for_foreground_tile_mesh)
{
   this->shader_for_foreground_tile_mesh = shader_for_foreground_tile_mesh;
}


void Basic2D::set_collision_tile_map(AllegroFlare::TileMaps::TileMap<int>* collision_tile_map)
{
   this->collision_tile_map = collision_tile_map;
}


void Basic2D::set_background_layers(std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> background_layers)
{
   this->background_layers = background_layers;
}


void Basic2D::set_image_layers(std::vector<AllegroFlare::Elements::ImageLayer> image_layers)
{
   this->image_layers = image_layers;
}


AllegroFlare::TileMaps::PrimMeshAtlas* Basic2D::get_tile_atlas() const
{
   return tile_atlas;
}


AllegroFlare::TileMaps::TileMesh* Basic2D::get_terrain_tile_mesh() const
{
   return terrain_tile_mesh;
}


AllegroFlare::Shaders::Base* Basic2D::get_shader_for_terrain_tile_mesh() const
{
   return shader_for_terrain_tile_mesh;
}


AllegroFlare::TileMaps::TileMesh* Basic2D::get_background_tile_mesh() const
{
   return background_tile_mesh;
}


AllegroFlare::Shaders::Base* Basic2D::get_shader_for_background_tile_mesh() const
{
   return shader_for_background_tile_mesh;
}


AllegroFlare::TileMaps::TileMesh* Basic2D::get_foreground_tile_mesh() const
{
   return foreground_tile_mesh;
}


AllegroFlare::Shaders::Base* Basic2D::get_shader_for_foreground_tile_mesh() const
{
   return shader_for_foreground_tile_mesh;
}


AllegroFlare::TileMaps::TileMap<int>* Basic2D::get_collision_tile_map() const
{
   return collision_tile_map;
}


std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> Basic2D::get_background_layers() const
{
   return background_layers;
}


std::vector<AllegroFlare::Elements::ImageLayer> Basic2D::get_image_layers() const
{
   return image_layers;
}


std::vector<AllegroFlare::Elements::ImageLayer> &Basic2D::get_image_layers_ref()
{
   return image_layers;
}


void Basic2D::update()
{
   // NOTE: No update on this entity
   return;
}

void Basic2D::draw()
{
   // NOTE: No draw on this entity.  Rendering is handled in the Gameplay/Screen
   return;
}

void Basic2D::destroy()
{
   // TODO: This destroy() method is now override. The location where destroy is called before this change was made
   // may be affected if another call to destroy() is added if this object is part of a collection of objects
   // TODO: There could potentially be dangling members left from these objects after they are deleted. Please
   // evaluate them individually to make sure they are not leaving anything dangling.
   if (tile_atlas)
   {
      delete tile_atlas;
      tile_atlas = nullptr;
   }
   if (terrain_tile_mesh)
   {
      delete terrain_tile_mesh;
      terrain_tile_mesh = nullptr;
   }
   if (background_tile_mesh)
   {
      delete background_tile_mesh;
      background_tile_mesh = nullptr;
   }
   if (foreground_tile_mesh)
   {
      delete foreground_tile_mesh;
      foreground_tile_mesh = nullptr;
   }
   if (collision_tile_map)
   {
      delete collision_tile_map;
      collision_tile_map= nullptr;
   }
   return;
}


} // namespace TileMaps
} // namespace Entities
} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


