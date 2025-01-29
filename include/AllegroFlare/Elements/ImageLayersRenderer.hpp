#pragma once


#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/Elements/ImageLayer.hpp>
#include <AllegroFlare/Shaders/TiledTintColor.hpp>
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
         AllegroFlare::Shaders::TiledTintColor* tiled_tint_color_shader;

      protected:


      public:
         ImageLayersRenderer(std::vector<AllegroFlare::Elements::ImageLayer>* image_layers=nullptr, AllegroFlare::Camera2D* camera=nullptr, AllegroFlare::Shaders::TiledTintColor* tiled_tint_color_shader=nullptr);
         ~ImageLayersRenderer();

         void set_image_layers(std::vector<AllegroFlare::Elements::ImageLayer>* image_layers);
         void set_camera(AllegroFlare::Camera2D* camera);
         void set_tiled_tint_color_shader(AllegroFlare::Shaders::TiledTintColor* tiled_tint_color_shader);
         std::vector<AllegroFlare::Elements::ImageLayer>* get_image_layers() const;
         AllegroFlare::Camera2D* get_camera() const;
         AllegroFlare::Shaders::TiledTintColor* get_tiled_tint_color_shader() const;
         void render();
      };
   }
}



