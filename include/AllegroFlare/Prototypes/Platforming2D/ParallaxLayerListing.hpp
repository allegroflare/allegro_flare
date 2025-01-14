#pragma once


#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Platforming2D
      {
         class ParallaxLayerListing
         {
         private:
            float anchor_x;
            float anchor_y;
            float offset_rate;
            std::string bitmap_identifier;

         protected:


         public:
            ParallaxLayerListing(float anchor_x=0.0f, float anchor_y=0.0f, float offset_rate=1.0, std::string bitmap_identifier="[unset-bitmap_identifier]");
            ~ParallaxLayerListing();

            void set_anchor_x(float anchor_x);
            void set_anchor_y(float anchor_y);
            void set_offset_rate(float offset_rate);
            void set_bitmap_identifier(std::string bitmap_identifier);
            float get_anchor_x() const;
            float get_anchor_y() const;
            float get_offset_rate() const;
            std::string get_bitmap_identifier() const;
         };
      }
   }
}



