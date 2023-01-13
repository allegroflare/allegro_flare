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
            class Basic : public AllegroFlare::TileMaps::AutoTile::Filters::Base
            {
            public:
               static constexpr char* TYPE = (char*)"Filters/Basic";

            private:
               std::string property;

            protected:


            public:
               Basic(std::string property="[unset-property]");
               virtual ~Basic();

               std::string get_property() const;
               virtual bool process() override;
            };
         }
      }
   }
}



