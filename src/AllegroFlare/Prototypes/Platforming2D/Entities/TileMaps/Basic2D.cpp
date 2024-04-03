

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


Basic2D::Basic2D()
   : AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D()
   , tile_atlas(nullptr)
   , tile_mesh(nullptr)
   , background_tile_mesh(nullptr)
   , collision_tile_mesh(nullptr)
{
}


Basic2D::~Basic2D()
{
}


void Basic2D::set_tile_atlas(AllegroFlare::TileMaps::PrimMeshAtlas* tile_atlas)
{
   this->tile_atlas = tile_atlas;
}


void Basic2D::set_tile_mesh(AllegroFlare::TileMaps::PrimMesh* tile_mesh)
{
   this->tile_mesh = tile_mesh;
}


void Basic2D::set_background_tile_mesh(AllegroFlare::TileMaps::PrimMesh* background_tile_mesh)
{
   this->background_tile_mesh = background_tile_mesh;
}


void Basic2D::set_collision_tile_mesh(AllegroFlare::TileMaps::TileMap<int>* collision_tile_mesh)
{
   this->collision_tile_mesh = collision_tile_mesh;
}


AllegroFlare::TileMaps::PrimMeshAtlas* Basic2D::get_tile_atlas() const
{
   return tile_atlas;
}


AllegroFlare::TileMaps::PrimMesh* Basic2D::get_tile_mesh() const
{
   return tile_mesh;
}


AllegroFlare::TileMaps::PrimMesh* Basic2D::get_background_tile_mesh() const
{
   return background_tile_mesh;
}


AllegroFlare::TileMaps::TileMap<int>* Basic2D::get_collision_tile_mesh() const
{
   return collision_tile_mesh;
}


void Basic2D::destroy()
{
   // TODO: There could potentially be dangling members left from these objects after they are deleted. Please
   // evaluate them individually to make sure they are not leaving anything dangling.
   if (tile_atlas)
   {
      delete tile_atlas;
      tile_atlas = nullptr;
   }
   if (tile_mesh)
   {
      delete tile_mesh;
      tile_mesh = nullptr;
   }
   if (background_tile_mesh)
   {
      delete background_tile_mesh;
      background_tile_mesh = nullptr;
   }
   if (collision_tile_mesh)
   {
      delete collision_tile_mesh;
      collision_tile_mesh = nullptr;
   }
   return;
}


} // namespace TileMaps
} // namespace Entities
} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


