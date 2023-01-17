#pragma once


#include <AllegroFlare/TileMaps/AutoTile/Filters/Base.hpp>
#include <cstdint>
#include <map>


namespace AllegroFlare
{
   namespace TileMaps
   {
      namespace AutoTile
      {
         namespace Filters
         {
            class FortyEightEdges : public AllegroFlare::TileMaps::AutoTile::Filters::Base
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
               static constexpr uint32_t EMPTY = 17;
               static constexpr uint32_t SOLID = 18;
               static constexpr uint32_t TOP_BL = 19;
               static constexpr uint32_t TOP_BR = 20;
               static constexpr uint32_t TL_BR = 21;
               static constexpr uint32_t TR_BL = 22;
               static constexpr uint32_t TL = 23;
               static constexpr uint32_t BR = 24;
               static constexpr uint32_t TR = 25;
               static constexpr uint32_t BL = 26;
               static constexpr uint32_t TL_TR = 27;
               static constexpr uint32_t BL_BR = 28;
               static constexpr uint32_t TL_BL = 29;
               static constexpr uint32_t TR_BR = 30;
               static constexpr uint32_t TOP_RIGHT_BOTTOM = 31;
               static constexpr uint32_t RIGHT_BOTTOM_LEFT = 32;
               static constexpr uint32_t BOTTOM_LEFT_TOP = 33;
               static constexpr uint32_t LEFT_TOP_RIGHT = 34;
               static constexpr uint32_t TOP_BOTTOM = 35;
               static constexpr uint32_t LEFT_RIGHT = 36;
               static constexpr uint32_t TOP_RIGHT_BOTTOM_LEFT = 37;
               static constexpr uint32_t BOTTOM_TL = 38;
               static constexpr uint32_t BOTTOM_TR = 39;
               static constexpr uint32_t TOP_LEFT_BR = 40;
               static constexpr uint32_t TOP_RIGHT_BL = 41;
               static constexpr uint32_t BOTTOM_LEFT_TR = 42;
               static constexpr uint32_t BOTTOM_RIGHT_TL = 43;
               static constexpr uint32_t TL_TR_BR = 44;
               static constexpr uint32_t TR_BR_BL = 45;
               static constexpr uint32_t BR_BL_TL = 46;
               static constexpr uint32_t BL_TL_TR = 47;
               static constexpr uint32_t TL_TR_BR_BL = 48;
               static constexpr uint32_t TOP_BR_BL = 49;
               static constexpr uint32_t RIGHT_BL_TR = 50;
               static constexpr uint32_t BOTTOM_TL_TR = 51;
               static constexpr uint32_t LEFT_TR_BR = 52;
               static constexpr uint32_t LEFT_TR = 53;
               static constexpr uint32_t LEFT_BR = 54;
               static constexpr uint32_t RIGHT_TL = 55;
               static constexpr uint32_t RIGHT_BL = 56;
               static constexpr char* TYPE = (char*)"Filters/FortyEightEdges";

            private:
               int solid_tile_value;
               std::map<uint32_t, int> forty_eight_edges_tiles_definition;

            protected:


            public:
               FortyEightEdges(int solid_tile_value=1, std::map<uint32_t, int> forty_eight_edges_tiles_definition=build_default_forty_eight_edges_tiles_definition());
               virtual ~FortyEightEdges();

               void set_solid_tile_value(int solid_tile_value);
               void set_forty_eight_edges_tiles_definition(std::map<uint32_t, int> forty_eight_edges_tiles_definition);
               int get_solid_tile_value() const;
               std::map<uint32_t, int> get_forty_eight_edges_tiles_definition() const;
               virtual bool process() override;
               void process_three_edge_filters();
               void process_three_tip_filters();
               void process_two_edge_with_tip_filters();
               void process_one_edge_one_tip();
               void process_one_edge_two_tips();
               void process_two_tip_filters();
               int get_tile_for(uint32_t edge_tile_name=UNDEF);
               static std::map<uint32_t, int> build_default_forty_eight_edges_tiles_definition();
            };
         }
      }
   }
}



