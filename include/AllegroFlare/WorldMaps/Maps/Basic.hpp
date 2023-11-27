#pragma once


#include <AllegroFlare/WorldMaps/Locations/Base.hpp>
#include <AllegroFlare/WorldMaps/Maps/Base.hpp>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace WorldMaps
   {
      namespace Maps
      {
         class Basic : public AllegroFlare::WorldMaps::Maps::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/WorldMaps/Maps/Basic";

         private:
            std::vector<AllegroFlare::WorldMaps::Locations::Base*> locations;

         protected:


         public:
            Basic(std::vector<AllegroFlare::WorldMaps::Locations::Base*> locations={});
            virtual ~Basic();

            void set_locations(std::vector<AllegroFlare::WorldMaps::Locations::Base*> locations);
            std::vector<AllegroFlare::WorldMaps::Locations::Base*> get_locations() const;
            virtual std::string location_id_at(float x=0, float y=0) override;
         };
      }
   }
}



