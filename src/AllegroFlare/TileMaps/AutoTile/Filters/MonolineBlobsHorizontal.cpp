

#include <AllegroFlare/TileMaps/AutoTile/Filters/MonolineBlobsHorizontal.hpp>

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


MonolineBlobsHorizontal::MonolineBlobsHorizontal(int solid_tile_value, std::map<uint32_t, int> monoline_blobs_horizontal_tiles_definition)
   : AllegroFlare::TileMaps::AutoTile::Filters::Base(AllegroFlare::TileMaps::AutoTile::Filters::MonolineBlobsHorizontal::TYPE)
   , solid_tile_value(solid_tile_value)
   , monoline_blobs_horizontal_tiles_definition(monoline_blobs_horizontal_tiles_definition)
{
}


MonolineBlobsHorizontal::~MonolineBlobsHorizontal()
{
}


void MonolineBlobsHorizontal::set_solid_tile_value(int solid_tile_value)
{
   this->solid_tile_value = solid_tile_value;
}


void MonolineBlobsHorizontal::set_monoline_blobs_horizontal_tiles_definition(std::map<uint32_t, int> monoline_blobs_horizontal_tiles_definition)
{
   this->monoline_blobs_horizontal_tiles_definition = monoline_blobs_horizontal_tiles_definition;
}


int MonolineBlobsHorizontal::get_solid_tile_value() const
{
   return solid_tile_value;
}


std::map<uint32_t, int> MonolineBlobsHorizontal::get_monoline_blobs_horizontal_tiles_definition() const
{
   return monoline_blobs_horizontal_tiles_definition;
}


bool MonolineBlobsHorizontal::process()
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
     { get_tile_for(SOLID) },
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
     { get_tile_for(EMPTY) },
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



   // left cap tile

   // Build our match_matrix for the "left cap tile fiter"
   std::vector<std::vector<int>> left_cap_tile_match_matrix = {
     // TODO: use ignore tile in corner tiles of this matrix
     { _, _, _ },
     { 0, s, s },
     { _, _, _ },
   };

   // Build our apply_matrix for the "left cap tile filter"
   std::vector<std::vector<int>> left_cap_tile_apply_matrix = {
     { _, _,                      _ },
     { _, get_tile_for(LEFT_CAP), _ },
     { _, _,                      _ },
   };

   iterate_through_input_and_apply_to_result_if_match(
      left_cap_tile_match_matrix,
      left_cap_tile_apply_matrix,
      1, // match_matrix_offset_x
      1, // match_matrix_offset_y
      1, // apply_matrix_offset_x
      1, // apply_matrix_offset_y
      match_type
   );



   // right cap tile

   // Build our match_matrix for the "right cap tile fiter"
   std::vector<std::vector<int>> right_cap_tile_match_matrix = {
     // TODO: use ignore tile in corner tiles of this matrix
     { _, _, _ },
     { s, s, 0 },
     { _, _, _ },
   };

   // Build our apply_matrix for the "right cap tile filter"
   std::vector<std::vector<int>> right_cap_tile_apply_matrix = {
     { _, _,                      _ },
     { _, get_tile_for(RIGHT_CAP), _ },
     { _, _,                      _ },
   };

   iterate_through_input_and_apply_to_result_if_match(
      right_cap_tile_match_matrix,
      right_cap_tile_apply_matrix,
      1, // match_matrix_offset_x
      1, // match_matrix_offset_y
      1, // apply_matrix_offset_x
      1, // apply_matrix_offset_y
      match_type
   );



   // isolated tile

   // Build our match_matrix for the "isolated cap tile fiter"
   std::vector<std::vector<int>> isolated_tile_match_matrix = {
     // TODO: use ignore tile in corner tiles of this matrix
     { _, 0, _ },
     { 0, s, 0 },
     { _, 0, _ },
   };

   // Build our apply_matrix for the "isolated tile filter"
   std::vector<std::vector<int>> isolated_tile_apply_matrix = {
     { _, _,                      _ },
     { _, get_tile_for(ISOLATED), _ },
     { _, _,                      _ },
   };

   iterate_through_input_and_apply_to_result_if_match(
      isolated_tile_match_matrix,
      isolated_tile_apply_matrix,
      1, // match_matrix_offset_x
      1, // match_matrix_offset_y
      1, // apply_matrix_offset_x
      1, // apply_matrix_offset_y
      match_type
   );



   // left gap tile

   // Build our match_matrix for the "left gap tile fiter"
   std::vector<std::vector<int>> left_gap_tile_match_matrix = {
     // TODO: use ignore tile in corner tiles of this matrix
     { s, s, _ },
     { 0, s, s },
     { s, s, _ },
   };

   // Build our apply_matrix for the "left gap tile filter"
   std::vector<std::vector<int>> left_gap_tile_apply_matrix = {
     { _, _,                      _ },
     { _, get_tile_for(LEFT_GAP), _ },
     { _, _,                      _ },
   };

   iterate_through_input_and_apply_to_result_if_match(
      left_gap_tile_match_matrix,
      left_gap_tile_apply_matrix,
      1, // match_matrix_offset_x
      1, // match_matrix_offset_y
      1, // apply_matrix_offset_x
      1, // apply_matrix_offset_y
      match_type
   );



   // right gap tile

   // Build our match_matrix for the "right gap tile fiter"
   std::vector<std::vector<int>> right_gap_tile_match_matrix = {
     // TODO: use ignore tile in corner tiles of this matrix
     { _, s, s },
     { s, s, 0 },
     { _, s, s },
   };

   // Build our apply_matrix for the "right gap tile filter"
   std::vector<std::vector<int>> right_gap_tile_apply_matrix = {
     { _, _,                      _ },
     { _, get_tile_for(RIGHT_GAP), _ },
     { _, _,                      _ },
   };

   iterate_through_input_and_apply_to_result_if_match(
      right_gap_tile_match_matrix,
      right_gap_tile_apply_matrix,
      1, // match_matrix_offset_x
      1, // match_matrix_offset_y
      1, // apply_matrix_offset_x
      1, // apply_matrix_offset_y
      match_type
   );



   return true;
}

int MonolineBlobsHorizontal::get_tile_for(uint32_t edge_tile_name)
{
   if (!((monoline_blobs_horizontal_tiles_definition.count(edge_tile_name) != 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::AutoTile::Filters::MonolineBlobsHorizontal::get_tile_for]: error: guard \"(monoline_blobs_horizontal_tiles_definition.count(edge_tile_name) != 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::AutoTile::Filters::MonolineBlobsHorizontal::get_tile_for]: error: guard \"(monoline_blobs_horizontal_tiles_definition.count(edge_tile_name) != 0)\" not met");
   }
   return monoline_blobs_horizontal_tiles_definition[edge_tile_name];
}

std::map<uint32_t, int> MonolineBlobsHorizontal::build_default_monoline_blobs_horizontal_tiles_definition()
{
   std::function<decltype(tile_coord_to_contiguous)> tc =
      AllegroFlare::TileMaps::AutoTile::Filters::Base::tile_coord_to_contiguous;
   int num_columns = 7;
   int xo = 0;

   std::map<uint32_t, int> result = {
      { UNDEF,        tc(0+xo, 0, num_columns) },
      { EMPTY,        tc(0+xo, 0, num_columns) },
      { SOLID,        tc(3+xo, 0, num_columns) },
      { ISOLATED,     tc(1+xo, 0, num_columns) },
      { LEFT_CAP,     tc(2+xo, 0, num_columns) },
      { RIGHT_CAP,    tc(4+xo, 0, num_columns) },
      { LEFT_GAP,     tc(5+xo, 0, num_columns) },
      { RIGHT_GAP,    tc(6+xo, 0, num_columns) },
   };
   return result;
}


} // namespace Filters
} // namespace AutoTile
} // namespace TileMaps
} // namespace AllegroFlare


