

#include <WickedDemos/TileMaps/Basic2D.hpp>




namespace WickedDemos
{
namespace TileMaps
{


Basic2D::Basic2D()
   : Wicked::Entities::Basic2D()
   , tile_atlas(nullptr)
   , tile_mesh(nullptr)
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


AllegroFlare::TileMaps::TileMap<int>* Basic2D::get_collision_tile_mesh() const
{
   return collision_tile_mesh;
}




} // namespace TileMaps
} // namespace WickedDemos


