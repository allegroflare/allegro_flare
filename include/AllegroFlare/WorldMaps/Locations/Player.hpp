#pragma once


#include <AllegroFlare/WorldMaps/Locations/Base.hpp>


namespace AllegroFlare
{
   namespace WorldMaps
   {
      namespace Locations
      {
         class Player : public AllegroFlare::WorldMaps::Locations::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/WorldMaps/Locations/Player";

         private:
            float x;
            float y;
            float width;
            float height;

         protected:


         public:
            Player(float x=0.0f, float y=0.0f, float width=30.0f, float height=30.0f);
            virtual ~Player();

            void set_x(float x);
            void set_y(float y);
            void set_width(float width);
            void set_height(float height);
            float get_x() const;
            float get_y() const;
            float get_width() const;
            float get_height() const;
            virtual bool collides(float point_x=0.0f, float point_y=0.0f) override;
         };
      }
   }
}



