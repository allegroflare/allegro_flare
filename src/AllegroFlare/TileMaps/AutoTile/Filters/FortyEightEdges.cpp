

#include <AllegroFlare/TileMaps/AutoTile/Filters/FortyEightEdges.hpp>

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


FortyEightEdges::FortyEightEdges(int solid_tile_value, std::map<uint32_t, int> forty_eight_edges_tiles_definition)
   : AllegroFlare::TileMaps::AutoTile::Filters::Base(AllegroFlare::TileMaps::AutoTile::Filters::FortyEightEdges::TYPE)
   , solid_tile_value(solid_tile_value)
   , forty_eight_edges_tiles_definition(forty_eight_edges_tiles_definition)
{
}


FortyEightEdges::~FortyEightEdges()
{
}


void FortyEightEdges::set_solid_tile_value(int solid_tile_value)
{
   this->solid_tile_value = solid_tile_value;
}


void FortyEightEdges::set_forty_eight_edges_tiles_definition(std::map<uint32_t, int> forty_eight_edges_tiles_definition)
{
   this->forty_eight_edges_tiles_definition = forty_eight_edges_tiles_definition;
}


int FortyEightEdges::get_solid_tile_value() const
{
   return solid_tile_value;
}


std::map<uint32_t, int> FortyEightEdges::get_forty_eight_edges_tiles_definition() const
{
   return forty_eight_edges_tiles_definition;
}


bool FortyEightEdges::process()
{
   // TODO: Finish this function
   AllegroFlare::TileMaps::AutoTile::FilterMatrix &input_matrix = get_input_matrix_ref();
   AllegroFlare::TileMaps::AutoTile::FilterMatrix &result_matrix = get_result_matrix_ref();
   int &s = solid_tile_value;
   int _ = -1;

   // Resize the result matrix
   result_matrix.resize(input_matrix.get_width(), input_matrix.get_height());



   // basic solid tile

   // Build our match_matrix for the "basic solid tile fiter"
   std::vector<std::vector<int>> basic_solid_tile_match_matrix = {
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
      0  // apply_matrix_offset_y
   );



   // basic empty tile

   // Build our match_matrix for the "basic empty tile fiter"
   std::vector<std::vector<int>> basic_empty_tile_match_matrix = {
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
      0  // apply_matrix_offset_y
   );



   // deep solid tile (this is not practically applied to anything in this case)

   // Build our match_matrix for the "deep solid tile fiter"
   std::vector<std::vector<int>> deep_solid_tile_match_matrix = {
     { _, s, _ },
     { s, s, s },
     { _, s, _ },
   };

   // Build our apply_matrix for the "deep solid tile filter"
   std::vector<std::vector<int>> deep_solid_tile_apply_matrix = {
     { _, _,                    _ },
     { _, get_tile_for(SOLID),  _ },
     { _, _,                    _ },
   };

   iterate_through_input_and_apply_to_result_if_match(
      deep_solid_tile_match_matrix,
      deep_solid_tile_apply_matrix,
      1, // match_matrix_offset_x
      1, // match_matrix_offset_y
      1, // apply_matrix_offset_x
      1  // apply_matrix_offset_y
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
      1  // apply_matrix_offset_y
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
      0  // apply_matrix_offset_y
   );



   // right wall tile

   // Build our match_matrix for the "right wall fiter"
   std::vector<std::vector<int>> right_wall_match_matrix = {
     { s, s, _ },
     { s, s, 0 },
     { s, s, _ },
   };

   // Build our apply_matrix for the "right wall filter"
   std::vector<std::vector<int>> right_wall_apply_matrix = {
     { get_tile_for(RIGHT) },
   };

   iterate_through_input_and_apply_to_result_if_match(
      right_wall_match_matrix,
      right_wall_apply_matrix,
      1, // match_matrix_offset_x
      1, // match_matrix_offset_y
      0, // apply_matrix_offset_x
      0  // apply_matrix_offset_y
   );



   // left wall tile

   // Build our match_matrix for the "left wall fiter"
   std::vector<std::vector<int>> left_wall_match_matrix = {
     { _, s, s },
     { 0, s, s },
     { _, s, s },
   };

   // Build our apply_matrix for the "left wall filter"
   std::vector<std::vector<int>> left_wall_apply_matrix = {
     { get_tile_for(LEFT) },
   };

   iterate_through_input_and_apply_to_result_if_match(
      left_wall_match_matrix,
      left_wall_apply_matrix,
      1, // match_matrix_offset_x
      1, // match_matrix_offset_y
      0, // apply_matrix_offset_x
      0  // apply_matrix_offset_y
   );



   // TOP BL

   // Build our match_matrix for the "top bl tile fiter"
   std::vector<std::vector<int>> top_bl_tile_match_matrix = {
     { _, 0, _ },
     { s, s, s },
     { 0, s, s },
   };

   // Build our apply_matrix for the "top bl tile filter"
   std::vector<std::vector<int>> top_bl_tile_apply_matrix = {
     { get_tile_for(TOP_BL) }, // TODO: behaves awkwardly on bottom left tile
   };

   iterate_through_input_and_apply_to_result_if_match(
      top_bl_tile_match_matrix,
      top_bl_tile_apply_matrix,
      1, // match_matrix_offset_x
      1, // match_matrix_offset_y
      0, // apply_matrix_offset_x
      0  // apply_matrix_offset_y
   );



   // TOP BR

   // Build our match_matrix for the "top br tile fiter"
   std::vector<std::vector<int>> top_br_tile_match_matrix = {
     { _, 0, _ },
     { s, s, s },
     { s, s, 0 },
   };

   // Build our apply_matrix for the "top br tile filter"
   std::vector<std::vector<int>> top_br_tile_apply_matrix = {
     { get_tile_for(TOP_BR) }, // TODO: behaves awkwardly on bottom left tile
   };

   iterate_through_input_and_apply_to_result_if_match(
      top_br_tile_match_matrix,
      top_br_tile_apply_matrix,
      1, // match_matrix_offset_x
      1, // match_matrix_offset_y
      0, // apply_matrix_offset_x
      0  // apply_matrix_offset_y
   );



   // TL BR

   // Build our match_matrix for the "tl br tile fiter"
   std::vector<std::vector<int>> tl_br_tile_match_matrix = {
     { 0, s, s },
     { s, s, s },
     { s, s, 0 },
   };

   // Build our apply_matrix for the "tl br tile filter"
   std::vector<std::vector<int>> tl_br_tile_apply_matrix = {
     { get_tile_for(TL_BR) }, // TODO: find edge cases (on result matrix) where it might be improperly stamped
   };

   iterate_through_input_and_apply_to_result_if_match(
      tl_br_tile_match_matrix,
      tl_br_tile_apply_matrix,
      1, // match_matrix_offset_x
      1, // match_matrix_offset_y
      0, // apply_matrix_offset_x
      0  // apply_matrix_offset_y
   );


   // TR BL

   // Build our match_matrix for the "tr bl tile fiter"
   std::vector<std::vector<int>> tr_bl_tile_match_matrix = {
     { s, s, 0 },
     { s, s, s },
     { 0, s, s },
   };

   // Build our apply_matrix for the "tr bl tile filter"
   std::vector<std::vector<int>> tr_bl_tile_apply_matrix = {
     { get_tile_for(TR_BL) }, // TODO: find edge cases (on result matrix) where it might be improperly stamped
   };

   iterate_through_input_and_apply_to_result_if_match(
      tr_bl_tile_match_matrix,
      tr_bl_tile_apply_matrix,
      1, // match_matrix_offset_x
      1, // match_matrix_offset_y
      0, // apply_matrix_offset_x
      0  // apply_matrix_offset_y
   );



   process_two_tip_filters();



   // TL

   // Build our match_matrix for the "tl tile fiter"
   std::vector<std::vector<int>> tl_tile_match_matrix = {
     { 0, s, s },
     { s, s, s },
     { s, s, s },
   };

   // Build our apply_matrix for the "tr bl tile filter"
   std::vector<std::vector<int>> tl_tile_apply_matrix = {
     { get_tile_for(TL) }, // TODO: find edge cases (on result matrix) where it might be improperly stamped
   };

   iterate_through_input_and_apply_to_result_if_match(
      tl_tile_match_matrix,
      tl_tile_apply_matrix,
      1, // match_matrix_offset_x
      1, // match_matrix_offset_y
      0, // apply_matrix_offset_x
      0  // apply_matrix_offset_y
   );


   // TR

   // Build our match_matrix for the "tr tile fiter"
   std::vector<std::vector<int>> tr_tile_match_matrix = {
     { s, s, 0 },
     { s, s, s },
     { s, s, s },
   };

   // Build our apply_matrix for the "tr bl tile filter"
   std::vector<std::vector<int>> tr_tile_apply_matrix = {
     { get_tile_for(TR) }, // TODO: find edge cases (on result matrix) where it might be improperly stamped
   };

   iterate_through_input_and_apply_to_result_if_match(
      tr_tile_match_matrix,
      tr_tile_apply_matrix,
      1, // match_matrix_offset_x
      1, // match_matrix_offset_y
      0, // apply_matrix_offset_x
      0  // apply_matrix_offset_y
   );



   // BL

   // Build our match_matrix for the "bl tile fiter"
   std::vector<std::vector<int>> bl_tile_match_matrix = {
     { s, s, s },
     { s, s, s },
     { 0, s, s },
   };

   // Build our apply_matrix for the "tr bl tile filter"
   std::vector<std::vector<int>> bl_tile_apply_matrix = {
     { get_tile_for(BL) }, // TODO: find edge cases (on result matrix) where it might be improperly stamped
   };

   iterate_through_input_and_apply_to_result_if_match(
      bl_tile_match_matrix,
      bl_tile_apply_matrix,
      1, // match_matrix_offset_x
      1, // match_matrix_offset_y
      0, // apply_matrix_offset_x
      0  // apply_matrix_offset_y
   );



   // BR

   // Build our match_matrix for the "br tile fiter"
   std::vector<std::vector<int>> br_tile_match_matrix = {
     { s, s, s },
     { s, s, s },
     { s, s, 0 },
   };

   // Build our apply_matrix for the "tr bl tile filter"
   std::vector<std::vector<int>> br_tile_apply_matrix = {
     { get_tile_for(BR) }, // TODO: find edge cases (on result matrix) where it might be improperly stamped
   };

   iterate_through_input_and_apply_to_result_if_match(
      br_tile_match_matrix,
      br_tile_apply_matrix,
      1, // match_matrix_offset_x
      1, // match_matrix_offset_y
      0, // apply_matrix_offset_x
      0  // apply_matrix_offset_y
   );



   // top left

   // Build our match_matrix for the "basic top_left tile fiter"
   std::vector<std::vector<int>> top_left_tile_match_matrix = {
     { _, 0, _ },
     { 0, s, s },
     { _, s, s },
   };

   // Build our apply_matrix for the "basic top_left tile filter"
   std::vector<std::vector<int>> top_left_tile_apply_matrix = {
     { get_tile_for(TOP_LEFT) },
   };

   iterate_through_input_and_apply_to_result_if_match(
      top_left_tile_match_matrix,
      top_left_tile_apply_matrix,
      1, // match_matrix_offset_x
      1, // match_matrix_offset_y
      0, // apply_matrix_offset_x
      0  // apply_matrix_offset_y
   );



   // top right

   // Build our match_matrix for the "basic top_right tile fiter"
   std::vector<std::vector<int>> top_right_tile_match_matrix = {
     { _, 0, _ },
     { s, s, 0 },
     { s, s, _ },
   };

   // Build our apply_matrix for the "basic top_right tile filter"
   std::vector<std::vector<int>> top_right_tile_apply_matrix = {
     { get_tile_for(TOP_RIGHT) },
   };

   iterate_through_input_and_apply_to_result_if_match(
      top_right_tile_match_matrix,
      top_right_tile_apply_matrix,
      1, // match_matrix_offset_x
      1, // match_matrix_offset_y
      0, // apply_matrix_offset_x
      0  // apply_matrix_offset_y
   );



   // bottom left

   // Build our match_matrix for the "basic bottom_left tile fiter"
   std::vector<std::vector<int>> bottom_left_tile_match_matrix = {
     { _, s, s },
     { 0, s, s },
     { _, 0, _ },
   };

   // Build our apply_matrix for the "basic bottom_left tile filter"
   std::vector<std::vector<int>> bottom_left_tile_apply_matrix = {
     { get_tile_for(BOTTOM_LEFT) },
   };

   iterate_through_input_and_apply_to_result_if_match(
      bottom_left_tile_match_matrix,
      bottom_left_tile_apply_matrix,
      1, // match_matrix_offset_x
      1, // match_matrix_offset_y
      0, // apply_matrix_offset_x
      0  // apply_matrix_offset_y
   );



   // bottom right

   // Build our match_matrix for the "basic bottom_right tile fiter"
   std::vector<std::vector<int>> bottom_right_tile_match_matrix = {
     { s, s, _ },
     { s, s, 0 },
     { _, 0, _ },
   };

   // Build our apply_matrix for the "basic bottom_right tile filter"
   std::vector<std::vector<int>> bottom_right_tile_apply_matrix = {
     { get_tile_for(BOTTOM_RIGHT) },
   };

   iterate_through_input_and_apply_to_result_if_match(
      bottom_right_tile_match_matrix,
      bottom_right_tile_apply_matrix,
      1, // match_matrix_offset_x
      1, // match_matrix_offset_y
      0, // apply_matrix_offset_x
      0  // apply_matrix_offset_y
   );



   return true;
}

void FortyEightEdges::process_two_tip_filters()
{
   AllegroFlare::TileMaps::AutoTile::FilterMatrix &input_matrix = get_input_matrix_ref();
   AllegroFlare::TileMaps::AutoTile::FilterMatrix &result_matrix = get_result_matrix_ref();
   int &s = solid_tile_value;
   int _ = -1;


   // TL TR

   // Build our match_matrix for the "tl tr tile fiter"
   std::vector<std::vector<int>> tl_tr_tile_match_matrix = {
     { 0, s, 0 },
     { s, s, s },
     { s, s, s },
   };

   // Build our apply_matrix for the "tl tr tile filter"
   std::vector<std::vector<int>> tl_tr_tile_apply_matrix = {
     { get_tile_for(TL_TR) }, // TODO: find edge cases (on result matrix) where it might be improperly stamped
   };

   iterate_through_input_and_apply_to_result_if_match(
      tl_tr_tile_match_matrix,
      tl_tr_tile_apply_matrix,
      1, // match_matrix_offset_x
      1, // match_matrix_offset_y
      0, // apply_matrix_offset_x
      0  // apply_matrix_offset_y
   );


   // BL BR

   // Build our match_matrix for the "bl br tile fiter"
   std::vector<std::vector<int>> bl_br_tile_match_matrix = {
     { s, s, s },
     { s, s, s },
     { 0, s, 0 },
   };

   // Build our apply_matrix for the "bl br tile filter"
   std::vector<std::vector<int>> bl_br_tile_apply_matrix = {
     { get_tile_for(BL_BR) }, // TODO: find edge cases (on result matrix) where it might be improperly stamped
   };

   iterate_through_input_and_apply_to_result_if_match(
      bl_br_tile_match_matrix,
      bl_br_tile_apply_matrix,
      1, // match_matrix_offset_x
      1, // match_matrix_offset_y
      0, // apply_matrix_offset_x
      0  // apply_matrix_offset_y
   );


   // TL BL

   // Build our match_matrix for the "tl bl tile fiter"
   std::vector<std::vector<int>> tl_bl_tile_match_matrix = {
     { 0, s, s },
     { s, s, s },
     { 0, s, s },
   };

   // Build our apply_matrix for the "tl bl tile filter"
   std::vector<std::vector<int>> tl_bl_tile_apply_matrix = {
     { get_tile_for(TL_BL) }, // TODO: find edge cases (on result matrix) where it might be improperly stamped
   };

   iterate_through_input_and_apply_to_result_if_match(
      tl_bl_tile_match_matrix,
      tl_bl_tile_apply_matrix,
      1, // match_matrix_offset_x
      1, // match_matrix_offset_y
      0, // apply_matrix_offset_x
      0  // apply_matrix_offset_y
   );


   // TR BR

   // Build our match_matrix for the "tr br tile fiter"
   std::vector<std::vector<int>> tr_br_tile_match_matrix = {
     { s, s, 0 },
     { s, s, s },
     { s, s, 0 },
   };

   // Build our apply_matrix for the "tl bl tile filter"
   std::vector<std::vector<int>> tr_br_tile_apply_matrix = {
     { get_tile_for(TR_BR) }, // TODO: find edge cases (on result matrix) where it might be improperly stamped
   };

   iterate_through_input_and_apply_to_result_if_match(
      tr_br_tile_match_matrix,
      tr_br_tile_apply_matrix,
      1, // match_matrix_offset_x
      1, // match_matrix_offset_y
      0, // apply_matrix_offset_x
      0  // apply_matrix_offset_y
   );
}

int FortyEightEdges::get_tile_for(uint32_t edge_tile_name)
{
   if (!((forty_eight_edges_tiles_definition.count(edge_tile_name) != 0)))
   {
      std::stringstream error_message;
      error_message << "[FortyEightEdges::get_tile_for]: error: guard \"(forty_eight_edges_tiles_definition.count(edge_tile_name) != 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FortyEightEdges::get_tile_for: error: guard \"(forty_eight_edges_tiles_definition.count(edge_tile_name) != 0)\" not met");
   }
   return forty_eight_edges_tiles_definition[edge_tile_name];
}

std::map<uint32_t, int> FortyEightEdges::build_default_forty_eight_edges_tiles_definition()
{
   std::function<decltype(tile_coord_to_contiguous)> tc =
      AllegroFlare::TileMaps::AutoTile::Filters::Base::tile_coord_to_contiguous;
   int num_columns = 12;

   // NOTE: The following abbreviations refer to edges only at tips:
   //    TL == "top left"
   //    BL == "botom left"
   //    TR == "top right"
   //    BR == "bottom right"

   std::map<uint32_t, int> result = {
      { UNDEF,        tc( 0,  0, num_columns) },
      { EMPTY,        tc(10,  1, num_columns) },
      { SOLID,        tc( 9,  2, num_columns) },

      // edges
      { TOP,          tc(10,  0, num_columns) },
      { BOTTOM,       tc( 9,  3, num_columns) },
      { RIGHT,        tc(11,  2, num_columns) },
      { LEFT,         tc( 8,  1, num_columns) },

      // corners
      { TOP_LEFT,     tc( 8,  0, num_columns) },
      { TOP_RIGHT,    tc(11,  0, num_columns) },
      { BOTTOM_LEFT,  tc( 8,  3, num_columns) },
      { BOTTOM_RIGHT, tc(11,  3, num_columns) },

      // edges with tips
      { TOP_BL,       tc( 5,  0, num_columns) },
      { TOP_BR,       tc( 6,  0, num_columns) },

      // tips only (diagonal tips only)
      { TL_BR,        tc( 9,  1, num_columns) },
      { TR_BL,        tc(10,  2, num_columns) },

      // tips only (on same edge)
      { TL_TR,        tc( 9,  0, num_columns) },
      { BL_BR,        tc(10,  3, num_columns) },
      { TL_BL,        tc( 8,  2, num_columns) },
      { TR_BR,        tc(11,  1, num_columns) },

      // tips only (single tip)
      { TL,           tc( 5,  1, num_columns) },
      { BR,           tc( 6,  2, num_columns) },
      { TR,           tc( 6,  1, num_columns) },
      { BL,           tc( 5,  2, num_columns) },

      //{ LEFT,         tc( 8,  1, num_columns) },
      //{ BOTTOM,       tc( 9,  3, num_columns) },
      //{ RIGHT,        tc(11,  2, num_columns) },
      //{ LEFT,         tc( 8,  1, num_columns) },

      // TODO: add new mappings for this fourty-eight-edges tileset
      //{ TOP_LEFT,     tc(1+xo, 0, num_columns) },
      //{ TOP,          tc(2+xo, 0, num_columns) },
      //{ TOP_RIGHT,    tc(3+xo, 0, num_columns) },
      //{ TOP_TIP,      tc(0+xo, 0, num_columns) },
      //{ LEFT,         tc(1+xo, 1, num_columns) },
      //{ FULL,         tc(1,    0, num_columns) }, // is this the same as "middle", "full", "center"
      //{ RIGHT,        tc(3+xo, 1, num_columns) },
      //{ CENTER,       tc(1,    0, num_columns) }, // is this the same as "middle", "full", "center"
      //{ BOTTOM_LEFT,  tc(1+xo, 2, num_columns) },
      //{ BOTTOM,       tc(2+xo, 2, num_columns) },
      //{ BOTTOM_RIGHT, tc(3+xo, 2, num_columns) },
      //{ BOTTOM_TIP,   tc(0+xo, 2, num_columns) },
      //{ LEFT_TIP,     tc(3+xo, 1, num_columns) },
      //{ MIDDLE,       tc(1,    0, num_columns) }, // is this the same as "middle", "full", "center"
      //{ RIGHT_TIP,    tc(3+xo, 3, num_columns) },
      //{ ISOLATED,     tc(0+xo, 3, num_columns) },
   };
   return result;
}


} // namespace Filters
} // namespace AutoTile
} // namespace TileMaps
} // namespace AllegroFlare


