#pragma once


#include <AllegroFlare/TileMaps/AutoTile/Filters/Base.hpp>
#include <vector>


namespace AllegroFlare
{
   namespace TileMaps
   {
      namespace AutoTile
      {
         namespace Filters
         {
            class BasicFloor : public AllegroFlare::TileMaps::AutoTile::Filters::Base
            {
            public:
               static constexpr char* TYPE = (char*)"Filters/BasicFloor";

            private:
               int floor_tile_value;

            protected:


            public:
               BasicFloor(int floor_tile_value=0);
               virtual ~BasicFloor();

               void set_floor_tile_value(int floor_tile_value);
               int get_floor_tile_value() const;
               virtual bool process() override;
               bool matrix_matches(std::vector<std::vector<int>> match_matrix={}, int x=0, int y=0);
            };
         }
      }
   }
}



