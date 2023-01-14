#pragma once


#include <AllegroFlare/TileMaps/AutoTile/Filters/Base.hpp>
#include <cstdint>
#include <map>
#include <vector>


namespace AllegroFlare
{
   namespace TileMaps
   {
      namespace AutoTile
      {
         namespace Filters
         {
            class SixteenEdges : public AllegroFlare::TileMaps::AutoTile::Filters::Base
            {
            public:
               static constexpr uint32_t UNDEF = 0;
               static constexpr uint32_t TOP_LEFT = 1;
               static constexpr uint32_t TOP = 2;
               static constexpr uint32_t TOP_RIGHT = 3;
               static constexpr uint32_t TOP_TIP = 4;
               static constexpr uint32_t LEFT = 5;
               static constexpr uint32_t FULL = 6;
               static constexpr uint32_t RIGHT = 7;
               static constexpr uint32_t CENTER = 8;
               static constexpr uint32_t BOTTOM_LEFT = 9;
               static constexpr uint32_t BOTTOM = 10;
               static constexpr uint32_t BOTTOM_RIGHT = 11;
               static constexpr uint32_t BOTTOM_TIP = 12;
               static constexpr uint32_t LEFT_TIP = 13;
               static constexpr uint32_t MIDDLE = 14;
               static constexpr uint32_t RIGHT_TIP = 15;
               static constexpr uint32_t ISOLATED = 16;
               static constexpr char* TYPE = (char*)"Filters/SixteenEdges";

            private:
               int solid_tile_value;
               std::map<uint32_t, int> sixteen_edges_tiles_definition;

            protected:


            public:
               SixteenEdges(int solid_tile_value=1, std::map<uint32_t, int> sixteen_edges_tiles_definition=build_default_sixteen_edges_tiles_definition());
               virtual ~SixteenEdges();

               void set_solid_tile_value(int solid_tile_value);
               void set_sixteen_edges_tiles_definition(std::map<uint32_t, int> sixteen_edges_tiles_definition);
               int get_solid_tile_value() const;
               std::map<uint32_t, int> get_sixteen_edges_tiles_definition() const;
               virtual bool process() override;
               bool matrix_matches(std::vector<std::vector<int>> match_matrix={}, int x=0, int y=0);
               int get_tile_for(uint32_t edge_tile_name=UNDEF);
               static int tile_coord_to_contiguous(int tile_x=0, int tile_y=0, int tile_atlas_num_columns=0);
               static std::map<uint32_t, int> build_default_sixteen_edges_tiles_definition();
            };
         }
      }
   }
}



