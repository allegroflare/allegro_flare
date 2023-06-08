

#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/EntityFactory.hpp>




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


} // namespace DynamicEntityPipeline
} // namespace GraphicsPipelines
} // namespace AllegroFlare


