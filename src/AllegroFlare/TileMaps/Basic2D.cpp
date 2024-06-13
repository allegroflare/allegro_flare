

#include <AllegroFlare/TileMaps/Basic2D.hpp>

#include <AllegroFlare/Random.hpp>
#include <allegro5/allegro.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace TileMaps
{


Basic2D::Basic2D(AllegroFlare::BitmapBin* bitmap_bin, std::string atlas_bitmap_filename, int atlas_bitmap_tile_width, int atlas_bitmap_tile_height)
   : bitmap_bin(bitmap_bin)
   , atlas_bitmap_filename(atlas_bitmap_filename)
   , atlas_bitmap_tile_width(atlas_bitmap_tile_width)
   , atlas_bitmap_tile_height(atlas_bitmap_tile_height)
   , atlas()
   , prim_mesh()
   , collision_tile_map()
   , initialized(false)
{
}


Basic2D::~Basic2D()
{
}


void Basic2D::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


AllegroFlare::BitmapBin* Basic2D::get_bitmap_bin() const
{
   return bitmap_bin;
}


std::string Basic2D::get_atlas_bitmap_filename() const
{
   return atlas_bitmap_filename;
}


int Basic2D::get_atlas_bitmap_tile_width() const
{
   return atlas_bitmap_tile_width;
}


int Basic2D::get_atlas_bitmap_tile_height() const
{
   return atlas_bitmap_tile_height;
}


AllegroFlare::TileMaps::PrimMeshAtlas &Basic2D::get_atlas_ref()
{
   return atlas;
}


AllegroFlare::TileMaps::PrimMesh &Basic2D::get_prim_mesh_ref()
{
   return prim_mesh;
}


AllegroFlare::TileMaps::TileMap<int> &Basic2D::get_collision_tile_map_ref()
{
   return collision_tile_map;
}


void Basic2D::set_atlas_configuration(std::string atlas_bitmap_filename, int atlas_bitmap_tile_width, int atlas_bitmap_tile_height)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::Basic2D::set_atlas_configuration]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::Basic2D::set_atlas_configuration]: error: guard \"(!initialized)\" not met");
   }
   this->atlas_bitmap_filename = atlas_bitmap_filename;
   this->atlas_bitmap_tile_width = atlas_bitmap_tile_width;
   this->atlas_bitmap_tile_height = atlas_bitmap_tile_height;
   return;
}

void Basic2D::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::Basic2D::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::Basic2D::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::Basic2D::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::Basic2D::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::Basic2D::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::Basic2D::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::Basic2D::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::Basic2D::initialize]: error: guard \"bitmap_bin\" not met");
   }
   ALLEGRO_BITMAP *source_bitmap = bitmap_bin->auto_get(atlas_bitmap_filename);
   atlas.duplicate_bitmap_and_load(source_bitmap, atlas_bitmap_tile_width, atlas_bitmap_tile_height, 0);

   prim_mesh.initialize();
   prim_mesh.set_atlas(&atlas);

   initialized = true;
   return;
}

int Basic2D::get_num_rows()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::Basic2D::get_num_rows]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::Basic2D::get_num_rows]: error: guard \"initialized\" not met");
   }
   return prim_mesh.get_num_rows();
}

int Basic2D::get_num_columns()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::Basic2D::get_num_columns]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::Basic2D::get_num_columns]: error: guard \"initialized\" not met");
   }
   return prim_mesh.get_num_columns();
}

void Basic2D::resize(int num_columns, int num_rows)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::Basic2D::resize]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::Basic2D::resize]: error: guard \"initialized\" not met");
   }
   prim_mesh.resize(num_columns, num_rows);
   return;
}

void Basic2D::rescale_tile_dimensions_to(float tile_width, float tile_height)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::Basic2D::rescale_tile_dimensions_to]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::Basic2D::rescale_tile_dimensions_to]: error: guard \"initialized\" not met");
   }
   if (!((tile_width > 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::Basic2D::rescale_tile_dimensions_to]: error: guard \"(tile_width > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::Basic2D::rescale_tile_dimensions_to]: error: guard \"(tile_width > 0)\" not met");
   }
   if (!((tile_height > 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::Basic2D::rescale_tile_dimensions_to]: error: guard \"(tile_height > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::Basic2D::rescale_tile_dimensions_to]: error: guard \"(tile_height > 0)\" not met");
   }
   prim_mesh.rescale_tile_dimensions_to(tile_width, tile_height);
   return;
}

void Basic2D::random_fill()
{
   AllegroFlare::Random random;
   int num_tiles_in_atlas = atlas.get_tile_index_size();
   for (int y=0; y<prim_mesh.get_num_rows(); y++)
      for (int x=0; x<prim_mesh.get_num_columns(); x++)
      {
         prim_mesh.set_tile_id(x, y, random.get_random_int(0, num_tiles_in_atlas-1));
      }
   return;
}

float Basic2D::infer_real_width()
{
   return prim_mesh.get_real_width();
}

float Basic2D::infer_real_height()
{
   return prim_mesh.get_real_height();
}

float Basic2D::obtain_tile_width()
{
   return prim_mesh.get_tile_width();
}

float Basic2D::obtain_tile_height()
{
   return prim_mesh.get_tile_height();
}

void Basic2D::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::Basic2D::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::Basic2D::render]: error: guard \"initialized\" not met");
   }
   prim_mesh.render();
   return;
}


} // namespace TileMaps
} // namespace AllegroFlare


