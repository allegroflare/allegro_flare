

#include <AllegroFlare/TileMaps/TileMesh.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace TileMaps
{


TileMesh::TileMesh(AllegroFlare::TileMaps::PrimMeshAtlas* atlas, int num_columns, int num_rows, int tile_width, int tile_height)
   : atlas(atlas)
   , vertexes()
   , vertex_buffer(nullptr)
   , tile_ids({})
   , num_columns(num_columns)
   , num_rows(num_rows)
   , tile_width(tile_width)
   , tile_height(tile_height)
   , yz_swapped(false)
   , initialized(false)
{
}


TileMesh::~TileMesh()
{
}


void TileMesh::set_atlas(AllegroFlare::TileMaps::PrimMeshAtlas* atlas)
{
   this->atlas = atlas;
}


AllegroFlare::TileMaps::PrimMeshAtlas* TileMesh::get_atlas() const
{
   return atlas;
}


std::vector<int> TileMesh::get_tile_ids() const
{
   return tile_ids;
}


int TileMesh::get_num_columns() const
{
   return num_columns;
}


int TileMesh::get_num_rows() const
{
   return num_rows;
}


int TileMesh::get_tile_width() const
{
   return tile_width;
}


int TileMesh::get_tile_height() const
{
   return tile_height;
}


bool TileMesh::get_initialized() const
{
   return initialized;
}


std::vector<ALLEGRO_VERTEX> &TileMesh::get_vertexes_ref()
{
   return vertexes;
}


void TileMesh::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[TileMesh::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TileMesh::initialize: error: guard \"(!initialized)\" not met");
   }
   // TODO: Guard on al_is_system_installed
   // TODO: Guard on al_is_primitives_addon_initialized
   return;
}

void TileMesh::resize(int num_columns, int num_rows)
{
   // TODO: This method body
   return;
}

void TileMesh::render(bool draw_outline)
{
   // TODO: This method body
   return;
}

void TileMesh::set_tile_id(int tile_x, int tile_y, int tile_id)
{
   // TODO: This method body
   return;
}

int TileMesh::get_tile_id(int tile_x, int tile_y)
{
   // TODO: This method body
   return 0;
}

void TileMesh::set_tile_uv(int tile_x, int tile_y, int u1, int v1, int u2, int v2)
{
   // NOTE: Should the uv coordinates be floats?
   // TODO: This method body
   return;
}

int TileMesh::infer_num_vertexes()
{
   // TODO: This method body
   return 0;
}

int TileMesh::infer_num_tiles()
{
   // TODO: This method body
   return 0;
}

void TileMesh::rescale_tile_dimensions_to(int new_tile_width, int new_tile_height)
{
   // TODO: This method body
   return;
}

void TileMesh::set_tile_width(int tile_width)
{
   // TODO: This method body
   return;
}

void TileMesh::set_tile_height(int tile_width)
{
   // TODO: This method body
   return;
}

int TileMesh::get_real_width()
{
   // TODO: This should be a float?
   // TODO: This method body
   return 0;
}

int TileMesh::get_real_height()
{
   // TODO: This should be a float?
   // TODO: This method body
   return 0;
}

void TileMesh::swap_yz()
{
   // TODO: This method body
   return;
}


} // namespace TileMaps
} // namespace AllegroFlare


