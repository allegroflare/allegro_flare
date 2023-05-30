

#include <AllegroFlare/TileMaps/AutoTile/Filters/MonolineBlobsHorizontal.hpp>




namespace AllegroFlare
{
namespace TileMaps
{
namespace AutoTile
{
namespace Filters
{


MonolineBlobsHorizontal::MonolineBlobsHorizontal(std::string property)
   : AllegroFlare::TileMaps::AutoTile::Filters::Base(AllegroFlare::TileMaps::AutoTile::Filters::MonolineBlobsHorizontal::TYPE)
   , property(property)
{
}


MonolineBlobsHorizontal::~MonolineBlobsHorizontal()
{
}


std::string MonolineBlobsHorizontal::get_property() const
{
   return property;
}


bool MonolineBlobsHorizontal::process()
{
   // TODO: finish the remaining match rules on this class
   AllegroFlare::TileMaps::AutoTile::FilterMatrix &input_matrix = get_input_matrix_ref();
   AllegroFlare::TileMaps::AutoTile::FilterMatrix &result_matrix = get_result_matrix_ref();
   int s = SOLID;
   int _ = -1;
   // NOTE: This match type seems to work for now, but may need to be reviewed (or a new match type introduced
   // in the future.)  Note that the default is OUT_OF_BOUNDS_MATCH_TYPE_EXTRUDED_EDGES (and should remain the 
   // preferred default.)
   std::string match_type = AllegroFlare::TileMaps::AutoTile::Filters::Base::OUT_OF_BOUNDS_MATCH_TYPE_POSITIVE;


   // Resize the result matrix
   result_matrix.resize(input_matrix.get_width(), input_matrix.get_height());


   /*
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
   */


   return true;
}


} // namespace Filters
} // namespace AutoTile
} // namespace TileMaps
} // namespace AllegroFlare


