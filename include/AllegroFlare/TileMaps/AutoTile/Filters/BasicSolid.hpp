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
            class BasicSolid : public AllegroFlare::TileMaps::AutoTile::Filters::Base
            {
            public:
               static constexpr char* TYPE = (char*)"Filters/BasicSolid";

            private:
               int solid_tile_value;

            protected:


            public:
               BasicSolid(int solid_tile_value=0);
               virtual ~BasicSolid();

               void set_solid_tile_value(int solid_tile_value);
               int get_solid_tile_value() const;
               virtual bool process() override;
               bool matrix_matches(std::vector<std::vector<int>> match_matrix={}, int x=0, int y=0);
            };
         }
      }
   }
}



