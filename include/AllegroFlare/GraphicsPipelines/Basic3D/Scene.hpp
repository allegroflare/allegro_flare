#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/GraphicsPipelines/Basic3D/Entity.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <string>
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
            std::vector<AllegroFlare::GraphicsPipelines::Basic3D::Entity> get_entities_ref();
            void initialize();
            void add_entity(std::string obj_identifier="[unset-obj_identifier]", std::string texture_bitmap_identifier="[unset-texture_bitmap_identifier]", AllegroFlare::Vec3D position=AllegroFlare::Vec3D({ 0, 0, 0 }), AllegroFlare::Vec3D rotation=AllegroFlare::Vec3D({ 0, 0, 0 }));
            void update();
            void render();
         };
      }
   }
}



