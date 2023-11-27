#pragma once


#include <string>


namespace AllegroFlare
{
   namespace WorldMaps
   {
      namespace Locations
      {
         class Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/WorldMaps/Locations/Base";

         private:
            std::string type;

         protected:


         public:
            Base(std::string type=AllegroFlare::WorldMaps::Locations::Base::TYPE);
            virtual ~Base();

            std::string get_type() const;
            virtual bool collides(float x=0.0f, float y=0.0f);
            bool is_type(std::string possible_type="");
         };
      }
   }
}



