

#include <Wicked/TileMaps/Basic2D.hpp>




namespace Wicked
{
namespace TileMaps
{


Basic2D::Basic2D()
   : Wicked::TileMaps::Base()
   , tile_atlas(nullptr)
   , tile_mesh(nullptr)
   , collision_tile_mesh(nullptr)
{
}


Basic2D::~Basic2D()
{
}


void Basic2D::set_tile_atlas(Tileo::Atlas* tile_atlas)
{
   this->tile_atlas = tile_atlas;
}


void Basic2D::set_tile_mesh(Tileo::Mesh* tile_mesh)
{
   this->tile_mesh = tile_mesh;
}


void Basic2D::set_collision_tile_mesh(Tileo::TileMap* collision_tile_mesh)
{
   this->collision_tile_mesh = collision_tile_mesh;
}


Tileo::Atlas* Basic2D::get_tile_atlas() const
{
   return tile_atlas;
}


Tileo::Mesh* Basic2D::get_tile_mesh() const
{
   return tile_mesh;
}


Tileo::TileMap* Basic2D::get_collision_tile_mesh() const
{
   return collision_tile_mesh;
}




} // namespace TileMaps
} // namespace Wicked


