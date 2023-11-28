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
            std::string background_image_identifier;
            std::map<std::string, AllegroFlare::WorldMaps::Locations::Base*> locations;
            float width;
            float height;

         protected:


         public:
            Basic(std::string background_image_identifier="[unset-background_image_identifier]", std::map<std::string, AllegroFlare::WorldMaps::Locations::Base*> locations={}, float width=0.0f, float height=0.0f);
            virtual ~Basic();

            void set_background_image_identifier(std::string background_image_identifier);
            void set_locations(std::map<std::string, AllegroFlare::WorldMaps::Locations::Base*> locations);
            void set_width(float width);
            void set_height(float height);
            std::string get_background_image_identifier() const;
            std::map<std::string, AllegroFlare::WorldMaps::Locations::Base*> get_locations() const;
            float get_width() const;
            float get_height() const;
            virtual std::string location_id_at(float x=0, float y=0) override;
         };
      }
   }
}



