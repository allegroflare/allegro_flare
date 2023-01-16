#pragma once


#include <AllegroFlare/TileMaps/AutoTile/FilterMatrix.hpp>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace TileMaps
   {
      namespace AutoTile
      {
         namespace Filters
         {
            class Base
            {
            public:
               static constexpr char* TYPE = (char*)"Filters/Base";
               static constexpr char* OUT_OF_BOUNDS_MATCH_TYPE_POSITIVE = (char*)"positive";
               static constexpr char* OUT_OF_BOUNDS_MATCH_TYPE_NEGATIVE = (char*)"negative";
               static constexpr char* OUT_OF_BOUNDS_MATCH_TYPE_EXTRUDED_EDGE = (char*)"extruded_edge";

            private:
               std::string type;
               AllegroFlare::TileMaps::AutoTile::FilterMatrix input_matrix;
               AllegroFlare::TileMaps::AutoTile::FilterMatrix result_matrix;

            protected:


            public:
               Base(std::string type=AllegroFlare::TileMaps::AutoTile::Filters::Base::TYPE, AllegroFlare::TileMaps::AutoTile::FilterMatrix input_matrix={});
               virtual ~Base();

               void set_input_matrix(AllegroFlare::TileMaps::AutoTile::FilterMatrix input_matrix);
               std::string get_type() const;
               AllegroFlare::TileMaps::AutoTile::FilterMatrix get_input_matrix() const;
               AllegroFlare::TileMaps::AutoTile::FilterMatrix get_result_matrix() const;
               AllegroFlare::TileMaps::AutoTile::FilterMatrix &get_input_matrix_ref();
               AllegroFlare::TileMaps::AutoTile::FilterMatrix &get_result_matrix_ref();
               virtual bool process();
               void iterate_through_input_and_apply_to_result_if_match(std::vector<std::vector<int>> match_matrix={}, std::vector<std::vector<int>> apply_matrix={}, int match_matrix_offset_x=0, int match_matrix_offset_y=0, int apply_matrix_offset_x=0, int apply_matrix_offset_y=0, bool ignore_if_negative_tile_value_on_match_matrix=true, std::string out_of_bounds_match_type=OUT_OF_BOUNDS_MATCH_TYPE_POSITIVE, bool ignore_write_if_negative_tile_value_on_stamp_tile=true, bool ignore_if_stamp_tile_is_out_of_bounds_on_result_matrix=true);
               bool matrix_matches(std::vector<std::vector<int>> match_matrix={}, int at_coord_x=0, int at_coord_y=0, int match_matrix_offset_x=0, int match_matrix_offset_y=0, bool ignore_if_negative_tile_value_on_match_matrix=true, std::string out_of_bounds_match_type=OUT_OF_BOUNDS_MATCH_TYPE_POSITIVE);
               void stamp_to_result(std::vector<std::vector<int>> stamp_matrix={}, int at_coord_x=0, int at_coord_y=0, int apply_matrix_offset_x=0, int apply_matrix_offset_y=0, bool ignore_write_if_negative_tile_value_on_stamp_tile=true, bool ignore_if_stamp_tile_is_out_of_bounds_on_result_matrix=true);
               static int tile_coord_to_contiguous(int tile_x=0, int tile_y=0, int tile_atlas_num_columns=0);
            };
         }
      }
   }
}



