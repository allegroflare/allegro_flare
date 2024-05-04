

#include <AllegroFlare/TileMaps/TileMesh.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace TileMaps
{


TileMesh::TileMesh()
   : atlas(nullptr)
   , vertexes()
   , vertex_buffer(nullptr)
   , tile_ids({})
   , num_columns(0)
   , num_rows(0)
   , tile_width(1)
   , tile_height(1)
   , yz_swapped(false)
   , initialized(false)
{
}


TileMesh::~TileMesh()
{
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


} // namespace TileMaps
} // namespace AllegroFlare


