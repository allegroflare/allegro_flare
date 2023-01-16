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
               int get_tile_for(uint32_t edge_tile_name=UNDEF);
               static std::map<uint32_t, int> build_default_forty_eight_edges_tiles_definition();
            };
         }
      }
   }
}



