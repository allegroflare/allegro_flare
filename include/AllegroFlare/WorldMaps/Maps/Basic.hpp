#pragma once


#include <AllegroFlare/WorldMaps/Locations/Base.hpp>
#include <AllegroFlare/WorldMaps/Maps/Base.hpp>
#include <map>
#include <string>


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
            std::map<std::string, AllegroFlare::WorldMaps::Locations::Base*> locations;

         protected:


         public:
            Basic(std::map<std::string, AllegroFlare::WorldMaps::Locations::Base*> locations={});
            virtual ~Basic();

            void set_locations(std::map<std::string, AllegroFlare::WorldMaps::Locations::Base*> locations);
            std::map<std::string, AllegroFlare::WorldMaps::Locations::Base*> get_locations() const;
            virtual std::string location_id_at(float x=0, float y=0) override;
         };
      }
   }
}



