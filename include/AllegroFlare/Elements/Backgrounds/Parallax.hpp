#pragma once


#include <AllegroFlare/Elements/Backgrounds/Base.hpp>
#include <AllegroFlare/Elements/Backgrounds/ParallaxLayer.hpp>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace Backgrounds
      {
         class Parallax : public AllegroFlare::Elements::Backgrounds::Base
         {
         private:
            std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> layers;
            float offset_x;
            float offset_y;

         protected:


         public:
            Parallax(std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> layers={}, float offset_x=0, float offset_y=0);
            virtual ~Parallax();

            void set_layers(std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> layers);
            void set_offset_x(float offset_x);
            void set_offset_y(float offset_y);
            std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> get_layers() const;
            float get_offset_x() const;
            float get_offset_y() const;
            virtual void render();
         };
      }
   }
}



