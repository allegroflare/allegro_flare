

#include <AllegroFlare/Prototypes/MindDive/TunnelMesh.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace MindDive
{


TunnelMesh::TunnelMesh()
   : tile_atlas(nullptr)
   , tile_mesh(nullptr)
   , collision_tile_mesh(nullptr)
{
}


TunnelMesh::~TunnelMesh()
{
}


void TunnelMesh::set_tile_atlas(AllegroFlare::TileMaps::PrimMeshAtlas* tile_atlas)
{
   this->tile_atlas = tile_atlas;
}


void TunnelMesh::set_tile_mesh(AllegroFlare::TileMaps::PrimMesh* tile_mesh)
{
   this->tile_mesh = tile_mesh;
}


void TunnelMesh::set_collision_tile_mesh(AllegroFlare::TileMaps::TileMap<int>* collision_tile_mesh)
{
   this->collision_tile_mesh = collision_tile_mesh;
}


AllegroFlare::TileMaps::PrimMeshAtlas* TunnelMesh::get_tile_atlas() const
{
   return tile_atlas;
}


AllegroFlare::TileMaps::PrimMesh* TunnelMesh::get_tile_mesh() const
{
   return tile_mesh;
}


AllegroFlare::TileMaps::TileMap<int>* TunnelMesh::get_collision_tile_mesh() const
{
   return collision_tile_mesh;
}


void TunnelMesh::TODO()
{
   // This class currently derives from Wicked::Entities::Basic2D so that the
   // it can be used in WickedDemo as an entity. Please factor this out
   // so that this class can be stand-alone.
   return;
}

void TunnelMesh::render()
{
   return;
}


} // namespace MindDive
} // namespace Prototypes
} // namespace AllegroFlare


