#pragma once


#include <AllegroFlare/Backgrounds/Base.hpp>
#include <AllegroFlare/Backgrounds/ParallaxLayer.hpp>
#include <vector>


namespace AllegroFlare
{
   namespace Backgrounds
   {
      class Parallax : public AllegroFlare::Backgrounds::Base
      {
      private:
         std::vector<AllegroFlare::Backgrounds::ParallaxLayer> layers;
         float offset_x;
         float offset_y;

      public:
         Parallax(std::vector<AllegroFlare::Backgrounds::ParallaxLayer> layers={}, float offset_x=0, float offset_y=0);
         virtual ~Parallax();

         void set_layers(std::vector<AllegroFlare::Backgrounds::ParallaxLayer> layers);
         void set_offset_x(float offset_x);
         void set_offset_y(float offset_y);
         std::vector<AllegroFlare::Backgrounds::ParallaxLayer> get_layers();
         float get_offset_x();
         float get_offset_y();
         virtual void render();
      };
   }
}



