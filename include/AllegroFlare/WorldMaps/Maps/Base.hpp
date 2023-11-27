#pragma once


#include <string>


namespace AllegroFlare
{
   namespace WorldMaps
   {
      namespace Maps
      {
         class Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/WorldMaps/Maps/Base";

         private:
            std::string type;

         protected:


         public:
            Base(std::string type=AllegroFlare::WorldMaps::Maps::Base::TYPE);
            virtual ~Base();

            std::string get_type() const;
            virtual std::string location_id_at(float x=0, float y=0);
         };
      }
   }
}



