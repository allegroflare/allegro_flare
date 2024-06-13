

#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/EntityFactory.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace GraphicsPipelines
{
namespace DynamicEntityPipeline
{


EntityFactory::EntityFactory(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::ModelBin* model_bin)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , model_bin(model_bin)
{
}


EntityFactory::~EntityFactory()
{
}


void EntityFactory::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void EntityFactory::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void EntityFactory::set_model_bin(AllegroFlare::ModelBin* model_bin)
{
   this->model_bin = model_bin;
}


AllegroFlare::BitmapBin* EntityFactory::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::FontBin* EntityFactory::get_font_bin() const
{
   return font_bin;
}


AllegroFlare::ModelBin* EntityFactory::get_model_bin() const
{
   return model_bin;
}


AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Camera3D* EntityFactory::create_camera_3d()
{
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Camera3D *result =
     new AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Camera3D();
   return result;
}

AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::StaticModel3D* EntityFactory::create_static_model_3d(std::string model_identifier, std::string model_texture_identifier, AllegroFlare::Placement3D placement)
{
   if (!(model_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityFactory::create_static_model_3d]: error: guard \"model_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityFactory::create_static_model_3d]: error: guard \"model_bin\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityFactory::create_static_model_3d]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityFactory::create_static_model_3d]: error: guard \"bitmap_bin\" not met");
   }
   // TODO: Add test for this
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::StaticModel3D *result =
      new AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::StaticModel3D(
         model_bin->auto_get(model_identifier),
         bitmap_bin->auto_get(model_texture_identifier),
         placement
      );
   return result;
}


} // namespace DynamicEntityPipeline
} // namespace GraphicsPipelines
} // namespace AllegroFlare


