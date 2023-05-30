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
            class MonolineBlobsHorizontal : public AllegroFlare::TileMaps::AutoTile::Filters::Base
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/TileMaps/AutoTile/Filters/MonolineBlobsHorizontal";

            public:

               enum
               {
                  UNDEF = 0,
                  EMPTY,
                  SOLID,
                  LEFT_TIP,
                  RIGHT_TIP,
                  LEFT_GAP,
                  RIGHT_GAP,
               };
            private:
               int solid_tile_value;
               std::map<uint32_t, int> monoline_blobs_horizontal_tiles_definition;

            protected:


            public:
               MonolineBlobsHorizontal(int solid_tile_value=1, std::map<uint32_t, int> monoline_blobs_horizontal_tiles_definition=build_default_monoline_blobs_horizontal_tiles_definition());
               virtual ~MonolineBlobsHorizontal();

               void set_solid_tile_value(int solid_tile_value);
               void set_monoline_blobs_horizontal_tiles_definition(std::map<uint32_t, int> monoline_blobs_horizontal_tiles_definition);
               int get_solid_tile_value() const;
               std::map<uint32_t, int> get_monoline_blobs_horizontal_tiles_definition() const;
               virtual bool process() override;
               int get_tile_for(uint32_t edge_tile_name=UNDEF);
               static std::map<uint32_t, int> build_default_monoline_blobs_horizontal_tiles_definition();
            };
         }
      }
   }
}



