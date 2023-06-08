

#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/StaticModel3D.hpp>




namespace AllegroFlare
{
namespace GraphicsPipelines
{
namespace DynamicEntityPipeline
{
namespace Entities
{


StaticModel3D::StaticModel3D(AllegroFlare::Model3D* model_3d, ALLEGRO_BITMAP* model_3d_texture, AllegroFlare::Placement3D placement)
   : AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::StaticModel3D::TYPE)
   , model_3d(model_3d)
   , model_3d_texture(model_3d_texture)
   , placement(placement)
{
}


StaticModel3D::~StaticModel3D()
{
}


void StaticModel3D::set_model_3d(AllegroFlare::Model3D* model_3d)
{
   this->model_3d = model_3d;
}


void StaticModel3D::set_model_3d_texture(ALLEGRO_BITMAP* model_3d_texture)
{
   this->model_3d_texture = model_3d_texture;
}


AllegroFlare::Model3D* StaticModel3D::get_model_3d() const
{
   return model_3d;
}


ALLEGRO_BITMAP* StaticModel3D::get_model_3d_texture() const
{
   return model_3d_texture;
}


AllegroFlare::Placement3D StaticModel3D::get_placement() const
{
   return placement;
}


AllegroFlare::Placement3D &StaticModel3D::get_placement_ref()
{
   return placement;
}




} // namespace Entities
} // namespace DynamicEntityPipeline
} // namespace GraphicsPipelines
} // namespace AllegroFlare


