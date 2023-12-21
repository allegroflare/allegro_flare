#pragma once


#include <AllegroFlare/WorldMaps/Locations/Base.hpp>
#include <AllegroFlare/WorldMaps/Maps/Base.hpp>
#include <map>
#include <string>
#include <utility>


namespace AllegroFlare
{
   namespace WorldMaps
   {
      namespace Maps
      {
         class Basic : public AllegroFlare::WorldMaps::Maps::Base
         {
         public:
            static constexpr char* DEFAULT_PRIMARY_POINT_OF_INTEREST_IDENTIFIER = (char*)"[unset-primary_point_of_interest_identifier]";
            static constexpr char* TYPE = (char*)"AllegroFlare/WorldMaps/Maps/Basic";

         private:
            std::string background_image_identifier;
            std::map<std::string, AllegroFlare::WorldMaps::Locations::Base*> locations;
            float width;
            float height;
            std::string primary_point_of_interest_identifier;

         protected:


         public:
            Basic(std::string background_image_identifier="[unset-background_image_identifier]", std::map<std::string, AllegroFlare::WorldMaps::Locations::Base*> locations={}, float width=0.0f, float height=0.0f, std::string primary_point_of_interest_identifier=DEFAULT_PRIMARY_POINT_OF_INTEREST_IDENTIFIER);
            virtual ~Basic();

            void set_background_image_identifier(std::string background_image_identifier);
            void set_locations(std::map<std::string, AllegroFlare::WorldMaps::Locations::Base*> locations);
            void set_width(float width);
            void set_height(float height);
            void set_primary_point_of_interest_identifier(std::string primary_point_of_interest_identifier);
            std::string get_background_image_identifier() const;
            std::map<std::string, AllegroFlare::WorldMaps::Locations::Base*> get_locations() const;
            float get_width() const;
            float get_height() const;
            std::string get_primary_point_of_interest_identifier() const;
            virtual std::pair<float, float> infer_primary_point_of_interest_coordinates() override;
            std::pair<bool, std::pair<float, float>> infer_location_coordinates(std::string location_id="[unset-location_id]");
            bool primary_point_of_interest_is_set();
            bool primary_point_of_interest_is_on_map();
            bool location_exists(std::string location_id="[unset-location_id]");
            AllegroFlare::WorldMaps::Locations::Base* find_location_by_id(std::string location_id="[unset-location_id]");
            virtual std::string location_id_at(float x=0, float y=0) override;
         };
      }
   }
}



