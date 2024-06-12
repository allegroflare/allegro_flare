

#include <AllegroFlare/TileMaps/AutoTile/Filters/SixteenEdges.hpp>

#include <functional>
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
   // TODO: finish the remaining match rules on this class
   AllegroFlare::TileMaps::AutoTile::FilterMatrix &input_matrix = get_input_matrix_ref();
   AllegroFlare::TileMaps::AutoTile::FilterMatrix &result_matrix = get_result_matrix_ref();
   int &s = solid_tile_value;
   int _ = -1;
   // NOTE: This match type seems to work for now, but may need to be reviewed (or a new match type introduced
   // in the future.)  Note that the default is OUT_OF_BOUNDS_MATCH_TYPE_EXTRUDED_EDGES (and should remain the 
   // preferred default.)
   std::string match_type = AllegroFlare::TileMaps::AutoTile::Filters::Base::OUT_OF_BOUNDS_MATCH_TYPE_POSITIVE;


   // Resize the result matrix
   result_matrix.resize(input_matrix.get_width(), input_matrix.get_height());



   // basic solid tile

   // Build our match_matrix for the "basic solid tile fiter"
   std::vector<std::vector<int>> basic_solid_tile_match_matrix = {
     // TODO: use ignore tile in corner tiles of this matrix
     { s },
   };

   // Build our apply_matrix for the "basic solid tile filter"
   std::vector<std::vector<int>> basic_solid_tile_apply_matrix = {
     { get_tile_for(MIDDLE) },
   };

   iterate_through_input_and_apply_to_result_if_match(
      basic_solid_tile_match_matrix,
      basic_solid_tile_apply_matrix,
      0, // match_matrix_offset_x
      0, // match_matrix_offset_y
      0, // apply_matrix_offset_x
      0, // apply_matrix_offset_y
      match_type
   );



   // basic empty tile

   // Build our match_matrix for the "basic empty tile fiter"
   std::vector<std::vector<int>> basic_empty_tile_match_matrix = {
     // TODO: use ignore tile in corner tiles of this matrix
     { 0 },
   };

   // Build our apply_matrix for the "basic empty tile filter"
   std::vector<std::vector<int>> basic_empty_tile_apply_matrix = {
     { 0 },
   };

   iterate_through_input_and_apply_to_result_if_match(
      basic_empty_tile_match_matrix,
      basic_empty_tile_apply_matrix,
      0, // match_matrix_offset_x
      0, // match_matrix_offset_y
      0, // apply_matrix_offset_x
      0, // apply_matrix_offset_y
      match_type
   );



   // deep solid tile (this is not practically applied to anything in this case)

   // Build our match_matrix for the "deep solid tile fiter"
   std::vector<std::vector<int>> deep_solid_tile_match_matrix = {
     // TODO: use ignore tile in corner tiles of this matrix
     { _, s, _ },
     { s, s, s },
     { _, s, _ },
   };

   // Build our apply_matrix for the "deep solid tile filter"
   std::vector<std::vector<int>> deep_solid_tile_apply_matrix = {
     { _, _,                    _ },
     { _, get_tile_for(MIDDLE), _ },
     { _, _,                    _ },
   };

   iterate_through_input_and_apply_to_result_if_match(
      deep_solid_tile_match_matrix,
      deep_solid_tile_apply_matrix,
      1, // match_matrix_offset_x
      1, // match_matrix_offset_y
      1, // apply_matrix_offset_x
      1, // apply_matrix_offset_y
      match_type
   );



   // floor tile

   // Build our match_matrix for the "floor tile fiter"
   std::vector<std::vector<int>> floor_tile_match_matrix = {
     { 0 },
     { s },
   };

   // Build our apply_matrix for the "floor tile filter"
   std::vector<std::vector<int>> floor_tile_apply_matrix = {
     { _                 },
     { get_tile_for(TOP) },
   };

   iterate_through_input_and_apply_to_result_if_match(
      floor_tile_match_matrix,
      floor_tile_apply_matrix,
      0, // match_matrix_offset_x
      1, // match_matrix_offset_y
      0, // apply_matrix_offset_x
      1, // apply_matrix_offset_y
      match_type
   );



   // ceiling tile

   // Build our match_matrix for the "ceiling tile fiter"
   std::vector<std::vector<int>> ceiling_tile_match_matrix = {
     { s },
     { 0 },
   };

   // Build our apply_matrix for the "ceiling tile filter"
   std::vector<std::vector<int>> ceiling_tile_apply_matrix = {
     { get_tile_for(BOTTOM) },
     { _                    },
   };

   iterate_through_input_and_apply_to_result_if_match(
      ceiling_tile_match_matrix,
      ceiling_tile_apply_matrix,
      0, // match_matrix_offset_x
      0, // match_matrix_offset_y
      0, // apply_matrix_offset_x
      0, // apply_matrix_offset_y
      match_type
   );


   return true;
}

int SixteenEdges::get_tile_for(uint32_t edge_tile_name)
{
   if (!((sixteen_edges_tiles_definition.count(edge_tile_name) != 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::AutoTile::Filters::SixteenEdges::get_tile_for]: error: guard \"(sixteen_edges_tiles_definition.count(edge_tile_name) != 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::AutoTile::Filters::SixteenEdges::get_tile_for]: error: guard \"(sixteen_edges_tiles_definition.count(edge_tile_name) != 0)\" not met");
   }
   return sixteen_edges_tiles_definition[edge_tile_name];
}

std::map<uint32_t, int> SixteenEdges::build_default_sixteen_edges_tiles_definition()
{
   std::function<decltype(tile_coord_to_contiguous)> tc =
      AllegroFlare::TileMaps::AutoTile::Filters::SixteenEdges::tile_coord_to_contiguous;
   int num_columns = 8;
   int xo = 4;

   std::map<uint32_t, int> result = {
      { UNDEF,        tc(0+xo, 0, num_columns) },
      { TOP_LEFT,     tc(1+xo, 0, num_columns) },
      { TOP,          tc(2+xo, 0, num_columns) },
      { TOP_RIGHT,    tc(3+xo, 0, num_columns) },
      { TOP_TIP,      tc(0+xo, 0, num_columns) },
      { LEFT,         tc(1+xo, 1, num_columns) },
      { FULL,         tc(1,    0, num_columns) }, // is this the same as "middle", "full", "center"
      { RIGHT,        tc(3+xo, 1, num_columns) },
      { CENTER,       tc(1,    0, num_columns) }, // is this the same as "middle", "full", "center"
      { BOTTOM_LEFT,  tc(1+xo, 2, num_columns) },
      { BOTTOM,       tc(2+xo, 2, num_columns) },
      { BOTTOM_RIGHT, tc(3+xo, 2, num_columns) },
      { BOTTOM_TIP,   tc(0+xo, 2, num_columns) },
      { LEFT_TIP,     tc(3+xo, 1, num_columns) },
      { MIDDLE,       tc(1,    0, num_columns) }, // is this the same as "middle", "full", "center"
      { RIGHT_TIP,    tc(3+xo, 3, num_columns) },
      { ISOLATED,     tc(0+xo, 3, num_columns) },
   };
   return result;
}


} // namespace Filters
} // namespace AutoTile
} // namespace TileMaps
} // namespace AllegroFlare


