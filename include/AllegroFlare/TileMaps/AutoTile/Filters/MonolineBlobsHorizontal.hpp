#pragma once


#include <AllegroFlare/TileMaps/AutoTile/Filters/Base.hpp>
#include <string>


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
                  EMPTY = 0,
                  SOLID,
                  LEFT_TIP,
                  RIGHT_TIP,
                  LEFT_GAP,
                  RIGHT_GAP,
               };
            private:
               std::string property;

            protected:


            public:
               MonolineBlobsHorizontal(std::string property="[unset-property]");
               virtual ~MonolineBlobsHorizontal();

               std::string get_property() const;
               virtual bool process() override;
            };
         }
      }
   }
}



