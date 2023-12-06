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
            float x;
            float y;

         protected:


         public:
            Base(std::string type=AllegroFlare::WorldMaps::Locations::Base::TYPE, float x=0.0f, float y=0.0f);
            virtual ~Base();

            void set_x(float x);
            void set_y(float y);
            std::string get_type() const;
            float get_x() const;
            float get_y() const;
            virtual bool collides(float x=0.0f, float y=0.0f);
            bool is_type(std::string possible_type="");
         };
      }
   }
}



