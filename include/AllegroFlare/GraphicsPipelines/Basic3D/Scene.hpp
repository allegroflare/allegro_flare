#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/GraphicsPipelines/Basic3D/Entity.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <vector>


namespace AllegroFlare
{
   namespace GraphicsPipelines
   {
      namespace Basic3D
      {
         class Scene
         {
         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::ModelBin* model_bin;
            AllegroFlare::Camera3D camera;
            std::vector<AllegroFlare::GraphicsPipelines::Basic3D::Entity> entities;
            bool initialized;

         protected:


         public:
            Scene();
            ~Scene();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_model_bin(AllegroFlare::ModelBin* model_bin);
            void set_camera(AllegroFlare::Camera3D camera);
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::ModelBin* get_model_bin() const;
            AllegroFlare::Camera3D &get_camera_ref();
            void initialize();
            void add_entity();
            void update();
            void render();
         };
      }
   }
}



