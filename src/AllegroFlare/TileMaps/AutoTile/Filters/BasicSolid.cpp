

#include <AllegroFlare/TileMaps/AutoTile/Filters/BasicSolid.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace TileMaps
{
namespace AutoTile
{
namespace Filters
{


BasicSolid::BasicSolid(int solid_tile_value)
   : AllegroFlare::TileMaps::AutoTile::Filters::Base(AllegroFlare::TileMaps::AutoTile::Filters::BasicSolid::TYPE)
   , solid_tile_value(solid_tile_value)
{
}


BasicSolid::~BasicSolid()
{
}


void BasicSolid::set_solid_tile_value(int solid_tile_value)
{
   this->solid_tile_value = solid_tile_value;
}


int BasicSolid::get_solid_tile_value() const
{
   return solid_tile_value;
}


bool BasicSolid::process()
{
   AllegroFlare::TileMaps::AutoTile::FilterMatrix &input_matrix = get_input_matrix_ref();
   AllegroFlare::TileMaps::AutoTile::FilterMatrix &result_matrix = get_result_matrix_ref();

   // Resize the result matrix
   result_matrix.resize(input_matrix.get_width(), input_matrix.get_height());

   // Create our filter match_matrix
   std::vector<std::vector<int>> match_matrix = {
     { 1 },
   };

   // Create our apply matrix
   std::vector<std::vector<int>> apply_this = {
     { solid_tile_value },
   };

   // Iterate through each tile looking for matches
   for (int y=0; y<input_matrix.get_height(); y++)
      for (int x=0; x<input_matrix.get_width(); x++)
      {
         if (matrix_matches(match_matrix, x, y)) result_matrix.set_tile(x, y, solid_tile_value);
      }

   return true;
}

bool BasicSolid::matrix_matches(std::vector<std::vector<int>> match_matrix, int x, int y)
{
   if (!(AllegroFlare::TileMaps::AutoTile::FilterMatrix::STATIC_is_valid(match_matrix)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::AutoTile::Filters::BasicSolid::matrix_matches]: error: guard \"AllegroFlare::TileMaps::AutoTile::FilterMatrix::STATIC_is_valid(match_matrix)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::AutoTile::Filters::BasicSolid::matrix_matches]: error: guard \"AllegroFlare::TileMaps::AutoTile::FilterMatrix::STATIC_is_valid(match_matrix)\" not met");
   }
   AllegroFlare::TileMaps::AutoTile::FilterMatrix &input_matrix = get_input_matrix_ref();
   return input_matrix.tile_matches(x, y, match_matrix[0][0]); // WARNING: this is hard-coded (0, 0)
}


} // namespace Filters
} // namespace AutoTile
} // namespace TileMaps
} // namespace AllegroFlare


