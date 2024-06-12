

#include <AllegroFlare/TileMaps/AutoTile/Filters/BasicFloor.hpp>

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


BasicFloor::BasicFloor(int floor_tile_value)
   : AllegroFlare::TileMaps::AutoTile::Filters::Base(AllegroFlare::TileMaps::AutoTile::Filters::BasicFloor::TYPE)
   , floor_tile_value(floor_tile_value)
{
}


BasicFloor::~BasicFloor()
{
}


void BasicFloor::set_floor_tile_value(int floor_tile_value)
{
   this->floor_tile_value = floor_tile_value;
}


int BasicFloor::get_floor_tile_value() const
{
   return floor_tile_value;
}


bool BasicFloor::process()
{
   AllegroFlare::TileMaps::AutoTile::FilterMatrix &input_matrix = get_input_matrix_ref();
   AllegroFlare::TileMaps::AutoTile::FilterMatrix &result_matrix = get_result_matrix_ref();

   // Resize the result matrix
   result_matrix.resize(input_matrix.get_width(), input_matrix.get_height());

   // Build our match_matrix
   std::vector<std::vector<int>> match_matrix = {
     { 0 },
     { 1 },
   };

   std::vector<std::vector<int>> apply_this = {
     { 0 },
     { floor_tile_value },
   };

   for (int y=0; y<input_matrix.get_height(); y++)
      for (int x=0; x<input_matrix.get_width(); x++)
      {
         if (matrix_matches(match_matrix, x, y))
         {
            //result_matrix.set_tile(x, y, floor_tile_value);
            result_matrix.set_tile_ignore_if_out_of_bounds(x, y+1, floor_tile_value);
         }
      }

   return true;
}

bool BasicFloor::matrix_matches(std::vector<std::vector<int>> match_matrix, int x, int y)
{
   if (!(AllegroFlare::TileMaps::AutoTile::FilterMatrix::STATIC_is_valid(match_matrix)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::AutoTile::Filters::BasicFloor::matrix_matches]: error: guard \"AllegroFlare::TileMaps::AutoTile::FilterMatrix::STATIC_is_valid(match_matrix)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::AutoTile::Filters::BasicFloor::matrix_matches]: error: guard \"AllegroFlare::TileMaps::AutoTile::FilterMatrix::STATIC_is_valid(match_matrix)\" not met");
   }
   AllegroFlare::TileMaps::AutoTile::FilterMatrix &input_matrix = get_input_matrix_ref();
   return (
         input_matrix.tile_matches(x, y,   match_matrix[0][0]) // WARNING: this is hard-coded (0, 0)
      && input_matrix.tile_matches(x, y+1, match_matrix[1][0]) // WARNING: this is hard-coded (0, 0)
   );
}


} // namespace Filters
} // namespace AutoTile
} // namespace TileMaps
} // namespace AllegroFlare


