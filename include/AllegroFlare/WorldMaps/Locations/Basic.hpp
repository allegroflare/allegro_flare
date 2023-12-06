#pragma once


#include <AllegroFlare/WorldMaps/Locations/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace WorldMaps
   {
      namespace Locations
      {
         class Basic : public AllegroFlare::WorldMaps::Locations::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/WorldMaps/Locations/Basic";

         private:
            std::string label;
            float width;
            float height;

         protected:


         public:
            Basic(std::string label="[unset-label]", float width=30.0f, float height=30.0f);
            virtual ~Basic();

            void set_label(std::string label);
            void set_width(float width);
            void set_height(float height);
            std::string get_label() const;
            float get_width() const;
            float get_height() const;
            virtual bool collides(float point_x=0.0f, float point_y=0.0f) override;
         };
      }
   }
}



