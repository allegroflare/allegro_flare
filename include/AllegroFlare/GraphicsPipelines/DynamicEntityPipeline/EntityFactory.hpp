#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/Camera3D.hpp>
#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/StaticModel3D.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Placement3D.hpp>
#include <string>


namespace AllegroFlare
{
   namespace GraphicsPipelines
   {
      namespace DynamicEntityPipeline
      {
         class EntityFactory
         {
         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            AllegroFlare::ModelBin* model_bin;

         protected:


         public:
            EntityFactory(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::ModelBin* model_bin=nullptr);
            ~EntityFactory();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_model_bin(AllegroFlare::ModelBin* model_bin);
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::FontBin* get_font_bin() const;
            AllegroFlare::ModelBin* get_model_bin() const;
            AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Camera3D* create_camera_3d();
            AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::StaticModel3D* create_static_model_3d(std::string model_identifier="[unset-model_identifier]", std::string model_texture_identifier="[unset-model_texture_identifier]", AllegroFlare::Placement3D placement={});
         };
      }
   }
}



