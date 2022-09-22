

#include <AllegroFlare/Prototypes/MindDive/TunnelMesh.hpp>

#include <AllegroFlare/Random.hpp>
#include <allegro5/allegro.h>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace MindDive
{


TunnelMesh::TunnelMesh(AllegroFlare::BitmapBin* bitmap_bin)
   : bitmap_bin(bitmap_bin)
   , atlas()
   , prim_mesh()
   , collision_tile_map()
   , initialized(false)
{
}


TunnelMesh::~TunnelMesh()
{
}


void TunnelMesh::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


AllegroFlare::BitmapBin* TunnelMesh::get_bitmap_bin() const
{
   return bitmap_bin;
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
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "TunnelMesh" << "::" << "initialize" << ": error: " << "guard \"bitmap_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   ALLEGRO_BITMAP *source_bitmap = bitmap_bin->auto_get("uv.png");
   atlas.duplicate_bitmap_and_load(source_bitmap, 100, 100, 0);
   // TODO: bitmap_bin->destroy["uv.png"]

   prim_mesh.initialize();
   prim_mesh.set_atlas(&atlas);
   //prim_mesh.rescale_tile_dimentions_to(32, 32);
   //prim_mesh.rescale_tile_dimentions_to(2, 2);
   //prim_mesh.resize(12, 32);

   //random_fill();

   initialized = true;
   return;
}

void TunnelMesh::random_fill()
{
   AllegroFlare::Random random;
   int num_tiles_in_atlas = 100;
   for (int y=0; y<prim_mesh.get_num_rows(); y++)
      for (int x=0; x<prim_mesh.get_num_columns(); x++)
      {
         prim_mesh.set_tile_id(x, y, random.get_random_int(0, num_tiles_in_atlas-1));
      }
   return;
}

float TunnelMesh::infer_real_width()
{
   return prim_mesh.get_real_width();
}

float TunnelMesh::infer_real_height()
{
   return prim_mesh.get_real_height();
}

float TunnelMesh::obtain_tile_width()
{
   return prim_mesh.get_tile_width();
}

float TunnelMesh::obtain_tile_height()
{
   return prim_mesh.get_tile_height();
}

void TunnelMesh::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "TunnelMesh" << "::" << "render" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   prim_mesh.render();
   return;
}


} // namespace MindDive
} // namespace Prototypes
} // namespace AllegroFlare


