#pragma once


#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/Elements/Backgrounds/Base.hpp>
#include <AllegroFlare/Elements/Backgrounds/ParallaxLayer.hpp>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace Backgrounds
      {
         class ParallaxWithZoom : public AllegroFlare::Elements::Backgrounds::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/Elements/Backgrounds/ParallaxWithZoom";

         private:
            std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> layers;
            AllegroFlare::Camera2D* camera;

         protected:


         public:
            ParallaxWithZoom(std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> layers={}, AllegroFlare::Camera2D* camera=nullptr);
            virtual ~ParallaxWithZoom();

            void set_layers(std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> layers);
            void set_camera(AllegroFlare::Camera2D* camera);
            std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> get_layers() const;
            AllegroFlare::Camera2D* get_camera() const;
            virtual void render();
         };
      }
   }
}



