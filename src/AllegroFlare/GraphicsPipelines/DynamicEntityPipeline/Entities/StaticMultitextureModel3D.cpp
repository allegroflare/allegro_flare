

#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/StaticMultitextureModel3D.hpp>




namespace AllegroFlare
{
namespace GraphicsPipelines
{
namespace DynamicEntityPipeline
{
namespace Entities
{


StaticMultitextureModel3D::StaticMultitextureModel3D(AllegroFlare::MultitextureModel3D* model_3d, ALLEGRO_BITMAP* model_3d_texture, AllegroFlare::Placement3D placement)
   : AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::StaticMultitextureModel3D::TYPE)
   , model_3d(model_3d)
   , model_3d_texture(model_3d_texture)
   , placement(placement)
{
}


StaticMultitextureModel3D::~StaticMultitextureModel3D()
{
}


void StaticMultitextureModel3D::set_model_3d(AllegroFlare::MultitextureModel3D* model_3d)
{
   this->model_3d = model_3d;
}


void StaticMultitextureModel3D::set_model_3d_texture(ALLEGRO_BITMAP* model_3d_texture)
{
   this->model_3d_texture = model_3d_texture;
}


AllegroFlare::MultitextureModel3D* StaticMultitextureModel3D::get_model_3d() const
{
   return model_3d;
}


ALLEGRO_BITMAP* StaticMultitextureModel3D::get_model_3d_texture() const
{
   return model_3d_texture;
}


AllegroFlare::Placement3D StaticMultitextureModel3D::get_placement() const
{
   return placement;
}


AllegroFlare::Placement3D &StaticMultitextureModel3D::get_placement_ref()
{
   return placement;
}




} // namespace Entities
} // namespace DynamicEntityPipeline
} // namespace GraphicsPipelines
} // namespace AllegroFlare


