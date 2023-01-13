#pragma once


#include <AllegroFlare/TileMaps/AutoTile/Filters/Base.hpp>


namespace AllegroFlare
{
   namespace TileMaps
   {
      namespace AutoTile
      {
         namespace Filters
         {
            class Basic : public AllegroFlare::TileMaps::AutoTile::Filters::Base
            {
            public:
               static constexpr char* TYPE = (char*)"Filters/Basic";

            private:
               int tile_value;

            protected:


            public:
               Basic(int tile_value=0);
               virtual ~Basic();

               void set_tile_value(int tile_value);
               int get_tile_value() const;
               virtual bool process() override;
            };
         }
      }
   }
}



