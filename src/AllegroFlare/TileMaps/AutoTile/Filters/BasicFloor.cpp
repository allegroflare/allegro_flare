

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


BasicFloor::BasicFloor(int solid_tile_value)
   : AllegroFlare::TileMaps::AutoTile::Filters::Base(AllegroFlare::TileMaps::AutoTile::Filters::BasicFloor::TYPE)
   , solid_tile_value(solid_tile_value)
{
}


BasicFloor::~BasicFloor()
{
}


void BasicFloor::set_solid_tile_value(int solid_tile_value)
{
   this->solid_tile_value = solid_tile_value;
}


int BasicFloor::get_solid_tile_value() const
{
   return solid_tile_value;
}


bool BasicFloor::process()
{
   // TODO: rename this class to BasicSolid

   AllegroFlare::TileMaps::AutoTile::FilterMatrix &input_matrix = get_input_matrix_ref();
   AllegroFlare::TileMaps::AutoTile::FilterMatrix &result_matrix = get_result_matrix_ref();


   // Resize the result matrix
   result_matrix.resize(input_matrix.get_width(), input_matrix.get_height());

   std::vector<std::vector<int>> match_matrix = {
     { 1 },
   };

   std::vector<std::vector<int>> apply_this = {
     { solid_tile_value },
   };

   // HERE:
   // TODO: Test if the if_match matrix fits, and if so, apply the apply_this matrix
   //for (int y=0; y<height; y++)
      //for (int x=0; x<width; x++)
         //result_matrix.set_tile(x, y, tile_value);

   return true;
}

bool BasicFloor::matrix_matches(std::vector<std::vector<int>> match_matrix, int x, int y)
{
   if (!(AllegroFlare::TileMaps::AutoTile::FilterMatrix::STATIC_is_valid(match_matrix)))
   {
      std::stringstream error_message;
      error_message << "[BasicFloor::matrix_matches]: error: guard \"AllegroFlare::TileMaps::AutoTile::FilterMatrix::STATIC_is_valid(match_matrix)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicFloor::matrix_matches: error: guard \"AllegroFlare::TileMaps::AutoTile::FilterMatrix::STATIC_is_valid(match_matrix)\" not met");
   }
   AllegroFlare::TileMaps::AutoTile::FilterMatrix &input_matrix = get_input_matrix_ref();
   return input_matrix.tile_matches(x, y, match_matrix[0][0]); // WARNING: this is hard-coded (0, 0)
}


} // namespace Filters
} // namespace AutoTile
} // namespace TileMaps
} // namespace AllegroFlare


