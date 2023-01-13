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
            class Fill : public AllegroFlare::TileMaps::AutoTile::Filters::Base
            {
            public:
               static constexpr char* TYPE = (char*)"Filters/Fill";

            private:
               int tile_value;

            protected:


            public:
               Fill(int tile_value=0);
               virtual ~Fill();

               void set_tile_value(int tile_value);
               int get_tile_value() const;
               virtual bool process() override;
            };
         }
      }
   }
}



