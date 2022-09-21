

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
   : atlas()
   , prim_mesh()
   , collision_tile_map()
   , initialized(false)
{
}


TunnelMesh::~TunnelMesh()
{
}


AllegroFlare::TileMaps::PrimMeshAtlas &TunnelMesh::get_atlas_ref()
{
   return atlas;
}


AllegroFlare::TileMaps::PrimMesh &TunnelMesh::get_prim_mesh_ref()
{
   return prim_mesh;
}


AllegroFlare::TileMaps::TileMap<int> &TunnelMesh::get_collision_tile_map_ref()
{
   return collision_tile_map;
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
   prim_mesh.initialize();
   prim_mesh.set_atlas(&atlas);
   prim_mesh.rescale_tile_dimentions_to(32, 32);
   prim_mesh.resize(16, 32);

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
   prim_mesh.render(true);
   return;
}


} // namespace MindDive
} // namespace Prototypes
} // namespace AllegroFlare


