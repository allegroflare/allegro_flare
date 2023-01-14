

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


SixteenEdges::SixteenEdges(int solid_tile_value, std::map<uint32_t, int> sixteen_edges_tiles_definition)
   : AllegroFlare::TileMaps::AutoTile::Filters::Base(AllegroFlare::TileMaps::AutoTile::Filters::SixteenEdges::TYPE)
   , solid_tile_value(solid_tile_value)
   , sixteen_edges_tiles_definition(sixteen_edges_tiles_definition)
{
}


SixteenEdges::~SixteenEdges()
{
}


void SixteenEdges::set_solid_tile_value(int solid_tile_value)
{
   this->solid_tile_value = solid_tile_value;
}


void SixteenEdges::set_sixteen_edges_tiles_definition(std::map<uint32_t, int> sixteen_edges_tiles_definition)
{
   this->sixteen_edges_tiles_definition = sixteen_edges_tiles_definition;
}


int SixteenEdges::get_solid_tile_value() const
{
   return solid_tile_value;
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

   // Build our match_matrix for the "floor tile fiter"
   std::vector<std::vector<int>> floor_tile_match_matrix = {
     { 0                },
     { solid_tile_value },
   };

   // Build our apply_matrix for the "floor tile filter"
   std::vector<std::vector<int>> floor_tile_apply_matrix = {
     { 0 },
     { get_tile_for(TOP) },
   };

   for (int y=0; y<input_matrix.get_height(); y++)
      for (int x=0; x<input_matrix.get_width(); x++)
      {
         if (matrix_matches(floor_tile_match_matrix, x, y))
         {
            //result_matrix.set_tile_ignore_if_out_of_bounds(x, y+1, floor_tile_apply_matrix[1][0] ); // NOTE: tile not modified
            result_matrix.set_tile_ignore_if_out_of_bounds(x, y+1, floor_tile_apply_matrix[1][0] ); // WARNING: hard-coded
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

int SixteenEdges::get_tile_for(uint32_t edge_tile_name)
{
   if (!((sixteen_edges_tiles_definition.count(edge_tile_name) != 0)))
   {
      std::stringstream error_message;
      error_message << "[SixteenEdges::get_tile_for]: error: guard \"(sixteen_edges_tiles_definition.count(edge_tile_name) != 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SixteenEdges::get_tile_for: error: guard \"(sixteen_edges_tiles_definition.count(edge_tile_name) != 0)\" not met");
   }
   return sixteen_edges_tiles_definition[edge_tile_name];
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
   if (!((tile_x < tile_atlas_num_columns)))
   {
      std::stringstream error_message;
      error_message << "[SixteenEdges::tile_coord_to_contiguous]: error: guard \"(tile_x < tile_atlas_num_columns)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SixteenEdges::tile_coord_to_contiguous: error: guard \"(tile_x < tile_atlas_num_columns)\" not met");
   }
   return tile_x + tile_y * tile_atlas_num_columns;
}

std::map<uint32_t, int> SixteenEdges::build_default_sixteen_edges_tiles_definition()
{
   std::function<decltype(tile_coord_to_contiguous)> tc =
      AllegroFlare::TileMaps::AutoTile::Filters::SixteenEdges::tile_coord_to_contiguous;
   int num_columns = 8;

   std::map<uint32_t, int> result = {
      { UNDEF,        tc(0, 0, num_columns) },
      { TOP_LEFT,     tc(1, 0, num_columns) },
      { TOP,          tc(2, 0, num_columns) },
      { TOP_RIGHT,    tc(4, 0, num_columns) },
      { TOP_TIP,      tc(0, 0, num_columns) },
      { LEFT,         tc(1, 1, num_columns) },
      { FULL,         tc(2, 1, num_columns) }, // is this the same as "middle", "full", "center"
      { RIGHT,        tc(3, 1, num_columns) },
      { CENTER,       tc(2, 1, num_columns) }, // is this the same as "middle", "full", "center"
      { BOTTOM_LEFT,  tc(1, 2, num_columns) },
      { BOTTOM,       tc(2, 2, num_columns) },
      { BOTTOM_RIGHT, tc(3, 2, num_columns) },
      { BOTTOM_TIP,   tc(0, 2, num_columns) },
      { LEFT_TIP,     tc(3, 1, num_columns) },
      { MIDDLE,       tc(2, 1, num_columns) }, // is this the same as "middle", "full", "center"
      { RIGHT_TIP,    tc(3, 3, num_columns) },
      { ISOLATED,     tc(0, 3, num_columns) },
   };
   return result;
}


} // namespace Filters
} // namespace AutoTile
} // namespace TileMaps
} // namespace AllegroFlare


