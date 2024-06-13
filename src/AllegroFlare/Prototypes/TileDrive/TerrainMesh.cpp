

#include <AllegroFlare/Prototypes/TileDrive/TerrainMesh.hpp>

#include <AllegroFlare/Random.hpp>
#include <allegro5/allegro.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace TileDrive
{


TerrainMesh::TerrainMesh(AllegroFlare::BitmapBin* bitmap_bin)
   : bitmap_bin(bitmap_bin)
   , atlas()
   , prim_mesh()
   , collision_tile_map()
   , atlas_bitmap_filename("[atlas_bitmap_filename-unset]")
   , atlas_bitmap_tile_width(1)
   , atlas_bitmap_tile_height(1)
   , initialized(false)
{
}


TerrainMesh::~TerrainMesh()
{
}


void TerrainMesh::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


AllegroFlare::BitmapBin* TerrainMesh::get_bitmap_bin() const
{
   return bitmap_bin;
}


std::string TerrainMesh::get_atlas_bitmap_filename() const
{
   return atlas_bitmap_filename;
}


int TerrainMesh::get_atlas_bitmap_tile_width() const
{
   return atlas_bitmap_tile_width;
}


int TerrainMesh::get_atlas_bitmap_tile_height() const
{
   return atlas_bitmap_tile_height;
}


AllegroFlare::TileMaps::PrimMeshAtlas &TerrainMesh::get_atlas_ref()
{
   return atlas;
}


AllegroFlare::TileMaps::PrimMesh &TerrainMesh::get_prim_mesh_ref()
{
   return prim_mesh;
}


AllegroFlare::TileMaps::TileMap<int> &TerrainMesh::get_collision_tile_map_ref()
{
   return collision_tile_map;
}


void TerrainMesh::set_atlas_configuration(std::string atlas_bitmap_filename, int atlas_bitmap_tile_width, int atlas_bitmap_tile_height)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::TerrainMesh::set_atlas_configuration]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::TerrainMesh::set_atlas_configuration]: error: guard \"(!initialized)\" not met");
   }
   this->atlas_bitmap_filename = atlas_bitmap_filename;
   this->atlas_bitmap_tile_width = atlas_bitmap_tile_width;
   this->atlas_bitmap_tile_height = atlas_bitmap_tile_height;
   return;
}

void TerrainMesh::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::TerrainMesh::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::TerrainMesh::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::TerrainMesh::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::TerrainMesh::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::TerrainMesh::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::TerrainMesh::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::TerrainMesh::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::TerrainMesh::initialize]: error: guard \"bitmap_bin\" not met");
   }
   ALLEGRO_BITMAP *source_bitmap = bitmap_bin->auto_get(atlas_bitmap_filename);
   atlas.duplicate_bitmap_and_load(source_bitmap, atlas_bitmap_tile_width, atlas_bitmap_tile_height, 0);

   prim_mesh.initialize();
   prim_mesh.set_atlas(&atlas);
   prim_mesh.swap_yz();

   collision_tile_map.initialize();

   initialized = true;
   return;
}

void TerrainMesh::resize(int num_columns, int num_rows)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::TerrainMesh::resize]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::TerrainMesh::resize]: error: guard \"initialized\" not met");
   }
   prim_mesh.resize(num_columns, num_rows);
   collision_tile_map.resize(num_columns, num_rows);
   return;
}

void TerrainMesh::rescale_tile_dimensions_to(float tile_width, float tile_height)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::TerrainMesh::rescale_tile_dimensions_to]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::TerrainMesh::rescale_tile_dimensions_to]: error: guard \"initialized\" not met");
   }
   if (!((tile_width > 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::TerrainMesh::rescale_tile_dimensions_to]: error: guard \"(tile_width > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::TerrainMesh::rescale_tile_dimensions_to]: error: guard \"(tile_width > 0)\" not met");
   }
   if (!((tile_height > 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::TerrainMesh::rescale_tile_dimensions_to]: error: guard \"(tile_height > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::TerrainMesh::rescale_tile_dimensions_to]: error: guard \"(tile_height > 0)\" not met");
   }
   prim_mesh.rescale_tile_dimensions_to(tile_width, tile_height);
   return;
}

float TerrainMesh::infer_real_width()
{
   return prim_mesh.get_real_width();
}

float TerrainMesh::infer_real_height()
{
   return prim_mesh.get_real_height();
}

float TerrainMesh::obtain_tile_width()
{
   return prim_mesh.get_tile_width();
}

float TerrainMesh::obtain_tile_height()
{
   return prim_mesh.get_tile_height();
}

float TerrainMesh::obtain_num_rows()
{
   return prim_mesh.get_num_rows();
}

float TerrainMesh::obtain_num_columns()
{
   return prim_mesh.get_num_columns();
}

void TerrainMesh::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::TerrainMesh::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::TerrainMesh::render]: error: guard \"initialized\" not met");
   }
   prim_mesh.render();
   return;
}

void TerrainMesh::random_fill()
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


} // namespace TileDrive
} // namespace Prototypes
} // namespace AllegroFlare


