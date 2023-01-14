

#include <AllegroFlare/TileMaps/AutoTile/Filters/SixteenEdges.hpp>

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


SixteenEdges::SixteenEdges(int floor_tile_value, std::map<uint32_t, int> sixteen_edges_tiles_definition)
   : AllegroFlare::TileMaps::AutoTile::Filters::Base(AllegroFlare::TileMaps::AutoTile::Filters::SixteenEdges::TYPE)
   , floor_tile_value(floor_tile_value)
   , sixteen_edges_tiles_definition(sixteen_edges_tiles_definition)
{
}


SixteenEdges::~SixteenEdges()
{
}


void SixteenEdges::set_floor_tile_value(int floor_tile_value)
{
   this->floor_tile_value = floor_tile_value;
}


void SixteenEdges::set_sixteen_edges_tiles_definition(std::map<uint32_t, int> sixteen_edges_tiles_definition)
{
   this->sixteen_edges_tiles_definition = sixteen_edges_tiles_definition;
}


int SixteenEdges::get_floor_tile_value() const
{
   return floor_tile_value;
}


std::map<uint32_t, int> SixteenEdges::get_sixteen_edges_tiles_definition() const
{
   return sixteen_edges_tiles_definition;
}


bool SixteenEdges::process()
{
   // TODO: this class
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

bool SixteenEdges::matrix_matches(std::vector<std::vector<int>> match_matrix, int x, int y)
{
   if (!(AllegroFlare::TileMaps::AutoTile::FilterMatrix::STATIC_is_valid(match_matrix)))
   {
      std::stringstream error_message;
      error_message << "[SixteenEdges::matrix_matches]: error: guard \"AllegroFlare::TileMaps::AutoTile::FilterMatrix::STATIC_is_valid(match_matrix)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SixteenEdges::matrix_matches: error: guard \"AllegroFlare::TileMaps::AutoTile::FilterMatrix::STATIC_is_valid(match_matrix)\" not met");
   }
   AllegroFlare::TileMaps::AutoTile::FilterMatrix &input_matrix = get_input_matrix_ref();
   return (
         input_matrix.tile_matches(x, y,   match_matrix[0][0]) // WARNING: this is hard-coded (0, 0)
      && input_matrix.tile_matches(x, y+1, match_matrix[1][0]) // WARNING: this is hard-coded (0, 0)
   );
}

int SixteenEdges::tile_coord_to_contiguous(int tile_x, int tile_y, int tile_atlas_num_columns)
{
   if (!((tile_atlas_num_columns > 0)))
   {
      std::stringstream error_message;
      error_message << "[SixteenEdges::tile_coord_to_contiguous]: error: guard \"(tile_atlas_num_columns > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SixteenEdges::tile_coord_to_contiguous: error: guard \"(tile_atlas_num_columns > 0)\" not met");
   }
   // TODO: this function
   return 0;
}

std::map<uint32_t, int> SixteenEdges::build_default_sixteen_edges_tiles_definition()
{
   //auto &bitmap = tile_coord_to_contiguous;
   auto bitmap = 0;
   auto c = 8; // num_columns_in_tilemap

   std::map<uint32_t, int> result = {
      { UNDEF,    bitmap },
      { TOP_LEFT, bitmap },
      { TOP,      bitmap },
      { TOP_RIGHT, bitmap },
      { TOP_TIP, bitmap },
      { LEFT, bitmap },
      { FULL, bitmap },
      { RIGHT, bitmap },
      { CENTER, bitmap },
      { BOTTOM_LEFT, bitmap },
      { BOTTOM, bitmap },
      { BOTTOM_RIGHT, bitmap },
      { BOTTOM_TIP, bitmap },
      { LEFT_TIP, bitmap },
      { MIDDLE, bitmap },
      { RIGHT_TIP, bitmap },
      { ISOLATED, bitmap },
   };
   return result;
}


} // namespace Filters
} // namespace AutoTile
} // namespace TileMaps
} // namespace AllegroFlare


