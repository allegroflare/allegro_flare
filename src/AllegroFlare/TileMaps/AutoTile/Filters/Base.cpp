

#include <AllegroFlare/TileMaps/AutoTile/Filters/Base.hpp>

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


Base::Base(std::string type, AllegroFlare::TileMaps::AutoTile::FilterMatrix input_matrix)
   : type(type)
   , input_matrix(input_matrix)
   , result_matrix({})
{
}


Base::~Base()
{
}


void Base::set_input_matrix(AllegroFlare::TileMaps::AutoTile::FilterMatrix input_matrix)
{
   this->input_matrix = input_matrix;
}


std::string Base::get_type() const
{
   return type;
}


AllegroFlare::TileMaps::AutoTile::FilterMatrix Base::get_input_matrix() const
{
   return input_matrix;
}


AllegroFlare::TileMaps::AutoTile::FilterMatrix Base::get_result_matrix() const
{
   return result_matrix;
}


AllegroFlare::TileMaps::AutoTile::FilterMatrix &Base::get_input_matrix_ref()
{
   return input_matrix;
}


AllegroFlare::TileMaps::AutoTile::FilterMatrix &Base::get_result_matrix_ref()
{
   return result_matrix;
}


bool Base::process()
{
   return true;
}

void Base::iterate_through_input_and_apply_to_result_if_match(std::vector<std::vector<int>> match_matrix, std::vector<std::vector<int>> apply_matrix, int match_matrix_offset_x, int match_matrix_offset_y, int apply_matrix_offset_x, int apply_matrix_offset_y, std::string out_of_bounds_match_type, bool ignore_if_negative_tile_value_on_match_matrix, bool ignore_write_if_negative_tile_value_on_stamp_tile, bool ignore_if_stamp_tile_is_out_of_bounds_on_result_matrix)
{
   if (!(AllegroFlare::TileMaps::AutoTile::FilterMatrix::STATIC_is_valid(match_matrix)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::AutoTile::Filters::Base::iterate_through_input_and_apply_to_result_if_match]: error: guard \"AllegroFlare::TileMaps::AutoTile::FilterMatrix::STATIC_is_valid(match_matrix)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::AutoTile::Filters::Base::iterate_through_input_and_apply_to_result_if_match]: error: guard \"AllegroFlare::TileMaps::AutoTile::FilterMatrix::STATIC_is_valid(match_matrix)\" not met");
   }
   if (!(AllegroFlare::TileMaps::AutoTile::FilterMatrix::STATIC_is_valid(apply_matrix)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::AutoTile::Filters::Base::iterate_through_input_and_apply_to_result_if_match]: error: guard \"AllegroFlare::TileMaps::AutoTile::FilterMatrix::STATIC_is_valid(apply_matrix)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::AutoTile::Filters::Base::iterate_through_input_and_apply_to_result_if_match]: error: guard \"AllegroFlare::TileMaps::AutoTile::FilterMatrix::STATIC_is_valid(apply_matrix)\" not met");
   }
   // TODO: come up with a better name for this function
   AllegroFlare::TileMaps::AutoTile::FilterMatrix &input_matrix = get_input_matrix_ref();
   AllegroFlare::TileMaps::AutoTile::FilterMatrix &result_matrix = get_result_matrix_ref();

   // Comb through the input_matrix and stamp the result if there is a match
   for (int y=0; y<input_matrix.get_height(); y++)
      for (int x=0; x<input_matrix.get_width(); x++)
      {
         bool matrix_match_is_positive = false;
         bool matrix_match_processed = false;
         //if (out_of_bounds_match_type == OUT_OF_BOUNDS_MATCH_TYPE_POSITIVE
               //|| out_of_bounds_match_type == OUT_OF_BOUNDS_MATCH_TYPE_NEGATIVE
            //)
         //{
            // NOTE: this logic is a little clunky, assuming that if it's not _MATCH_TYPE_POSITIVE then implicitly
            // assuming it will be negative.
            //bool out_of_bounds_on_input_matrix_is_positive_match =
                     //(out_of_bounds_match_type == OUT_OF_BOUNDS_MATCH_TYPE_POSITIVE) ? true : false;

            matrix_match_is_positive = matrix_matches(
               match_matrix,
               x,
               y,
               match_matrix_offset_x,
               match_matrix_offset_y,
               ignore_if_negative_tile_value_on_match_matrix,
               out_of_bounds_match_type
            );
            //matrix_match_processed = true;
         //}

         //if (!matrix_match_processed)
         //{
            //throw std::runtime_error("AutoTile::Filters::Base::iterate_through_input_and_apply_to_result_if_match: "
                                     //"error: Unexpected behavior, matrix match not processed as expected.");
         //}

         if (matrix_match_is_positive)
         {
            stamp_to_result(
               apply_matrix,
               x,
               y,
               apply_matrix_offset_x,
               apply_matrix_offset_y,
               ignore_write_if_negative_tile_value_on_stamp_tile,
               ignore_if_stamp_tile_is_out_of_bounds_on_result_matrix
            );
         }
      }
   return;
}

bool Base::matrix_matches(std::vector<std::vector<int>> match_matrix, int at_coord_x, int at_coord_y, int match_matrix_offset_x, int match_matrix_offset_y, bool ignore_if_negative_tile_value_on_match_matrix, std::string out_of_bounds_match_type)
{
   if (!(AllegroFlare::TileMaps::AutoTile::FilterMatrix::STATIC_is_valid(match_matrix)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::AutoTile::Filters::Base::matrix_matches]: error: guard \"AllegroFlare::TileMaps::AutoTile::FilterMatrix::STATIC_is_valid(match_matrix)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::AutoTile::Filters::Base::matrix_matches]: error: guard \"AllegroFlare::TileMaps::AutoTile::FilterMatrix::STATIC_is_valid(match_matrix)\" not met");
   }
   // TODO: un-hardcode this function (note is done, just leaving commented code preserved in case of needed revert)
   AllegroFlare::TileMaps::AutoTile::FilterMatrix &input_matrix = get_input_matrix_ref();
   int match_matrix_width = match_matrix[0].size();
   int match_matrix_height = match_matrix.size();

   int out_of_bounds_match_type_i = 0;
   if (out_of_bounds_match_type == OUT_OF_BOUNDS_MATCH_TYPE_POSITIVE) out_of_bounds_match_type_i = 1;
   if (out_of_bounds_match_type == OUT_OF_BOUNDS_MATCH_TYPE_NEGATIVE) out_of_bounds_match_type_i = 2;
   if (out_of_bounds_match_type == OUT_OF_BOUNDS_MATCH_TYPE_EXTRUDED_EDGE) out_of_bounds_match_type_i = 3;

   // NOTE: This code is fragmented; Consider a refactor that does not have so many branching cases
   bool out_of_bounds_on_input_is_positive_match =
      (out_of_bounds_match_type == OUT_OF_BOUNDS_MATCH_TYPE_POSITIVE) ? true : false;

   for (int y=0; y<match_matrix_height; y++)
      for (int x=0; x<match_matrix_width; x++)
      {
         int match_matrix_tile_value = match_matrix[y][x];
         if (ignore_if_negative_tile_value_on_match_matrix && match_matrix_tile_value < 0) continue;

         switch (out_of_bounds_match_type_i)
         {
            case 1:
            // no break;
            case 2:
               if (!input_matrix.tile_matches(
                        at_coord_x + x - match_matrix_offset_x,
                        at_coord_y + y - match_matrix_offset_y,
                        match_matrix_tile_value,
                        out_of_bounds_on_input_is_positive_match
                     )
               ) return false;
            break;

            case 3:
               if (!input_matrix.tile_matches_with_extruded_boundaries(
                        at_coord_x + x - match_matrix_offset_x,
                        at_coord_y + y - match_matrix_offset_y,
                        match_matrix_tile_value
                     )
               ) return false;
            break;

            default:
              throw std::runtime_error("AutoTile::Filters::Base::matrix_matches: error: Unhandled case for "
                                       "out_of_bounds_match_type.");
            break;
         }
      }
   return true;

   //return (
         //input_matrix.tile_matches(at_coord_x, at_coord_y,   match_matrix[0][0]) // WARNING: this is hard-coded (0, 0)
      //&& input_matrix.tile_matches(at_coord_x, at_coord_y+1, match_matrix[1][0]) // WARNING: this is hard-coded (0, 0)
   //);
}

void Base::stamp_to_result(std::vector<std::vector<int>> stamp_matrix, int at_coord_x, int at_coord_y, int apply_matrix_offset_x, int apply_matrix_offset_y, bool ignore_write_if_negative_tile_value_on_stamp_tile, bool ignore_if_stamp_tile_is_out_of_bounds_on_result_matrix)
{
   if (!(AllegroFlare::TileMaps::AutoTile::FilterMatrix::STATIC_is_valid(stamp_matrix)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::AutoTile::Filters::Base::stamp_to_result]: error: guard \"AllegroFlare::TileMaps::AutoTile::FilterMatrix::STATIC_is_valid(stamp_matrix)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::AutoTile::Filters::Base::stamp_to_result]: error: guard \"AllegroFlare::TileMaps::AutoTile::FilterMatrix::STATIC_is_valid(stamp_matrix)\" not met");
   }
   // TODO: consider removing "STATIC_is_valid" guard for performance
   AllegroFlare::TileMaps::AutoTile::FilterMatrix &result_matrix = get_result_matrix_ref();
   int stamp_matrix_width = stamp_matrix[0].size();
   int stamp_matrix_height = stamp_matrix.size();

   for (int y=0; y<stamp_matrix_height; y++)
      for (int x=0; x<stamp_matrix_width; x++)
      {
         // Get the stamp value
         int stamp_tile_value = stamp_matrix[y][x];
         // Skip if we don't want negative stamp values
         if (ignore_write_if_negative_tile_value_on_stamp_tile && stamp_tile_value < 0) continue;

         if (ignore_if_stamp_tile_is_out_of_bounds_on_result_matrix)
         {
            // TODO: use "apply_matrix_offset_x" and "apply_matrix_offset_y"
            result_matrix.set_tile_ignore_if_out_of_bounds(
               at_coord_x + x - apply_matrix_offset_x,
               at_coord_y + y - apply_matrix_offset_y,
               stamp_tile_value
            );
         }
         else
         {
            // TODO: use "apply_matrix_offset_x" and "apply_matrix_offset_y"
            // TODO: test this case
            result_matrix.set_tile(
               at_coord_x + x - apply_matrix_offset_x,
               at_coord_y + y - apply_matrix_offset_y,
               stamp_tile_value
            );
         }
      }

   return;
}

int Base::tile_coord_to_contiguous(int tile_x, int tile_y, int tile_atlas_num_columns)
{
   if (!((tile_atlas_num_columns > 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::AutoTile::Filters::Base::tile_coord_to_contiguous]: error: guard \"(tile_atlas_num_columns > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::AutoTile::Filters::Base::tile_coord_to_contiguous]: error: guard \"(tile_atlas_num_columns > 0)\" not met");
   }
   if (!((tile_x < tile_atlas_num_columns)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::AutoTile::Filters::Base::tile_coord_to_contiguous]: error: guard \"(tile_x < tile_atlas_num_columns)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::AutoTile::Filters::Base::tile_coord_to_contiguous]: error: guard \"(tile_x < tile_atlas_num_columns)\" not met");
   }
   return tile_x + tile_y * tile_atlas_num_columns;
}


} // namespace Filters
} // namespace AutoTile
} // namespace TileMaps
} // namespace AllegroFlare


