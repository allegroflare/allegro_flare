#pragma once


#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/Elements/ImageLayer.hpp>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      class ImageLayersRenderer
      {
      private:
         std::vector<AllegroFlare::Elements::ImageLayer>* image_layers;
         AllegroFlare::Camera2D* camera;

      protected:


      public:
         ImageLayersRenderer(std::vector<AllegroFlare::Elements::ImageLayer>* image_layers=nullptr, AllegroFlare::Camera2D* camera=nullptr);
         ~ImageLayersRenderer();

         void set_image_layers(std::vector<AllegroFlare::Elements::ImageLayer>* image_layers);
         void set_camera(AllegroFlare::Camera2D* camera);
         std::vector<AllegroFlare::Elements::ImageLayer>* get_image_layers() const;
         AllegroFlare::Camera2D* get_camera() const;
         void render();
      };
   }
}



