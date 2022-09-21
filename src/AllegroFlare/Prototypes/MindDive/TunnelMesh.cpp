

#include <AllegroFlare/Prototypes/MindDive/TunnelMesh.hpp>

#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace MindDive
{


TunnelMesh::TunnelMesh()
   : tile_atlas()
   , tile_mesh()
   , collision_tile_mesh()
   , initialized(false)
{
}


TunnelMesh::~TunnelMesh()
{
}


AllegroFlare::TileMaps::PrimMeshAtlas &TunnelMesh::get_tile_atlas_ref()
{
   return tile_atlas;
}


AllegroFlare::TileMaps::PrimMesh &TunnelMesh::get_tile_mesh_ref()
{
   return tile_mesh;
}


AllegroFlare::TileMaps::TileMap<int> &TunnelMesh::get_collision_tile_mesh_ref()
{
   return collision_tile_mesh;
}


void TunnelMesh::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "TunnelMesh" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "TunnelMesh" << "::" << "initialize" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "TunnelMesh" << "::" << "initialize" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
   initialized = true;
   return;
}

void TunnelMesh::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "TunnelMesh" << "::" << "render" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   return;
}


} // namespace MindDive
} // namespace Prototypes
} // namespace AllegroFlare


