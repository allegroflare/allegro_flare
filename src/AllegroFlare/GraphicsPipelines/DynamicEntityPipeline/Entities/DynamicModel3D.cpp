

#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/DynamicModel3D.hpp>




namespace AllegroFlare
{
namespace GraphicsPipelines
{
namespace DynamicEntityPipeline
{
namespace Entities
{


DynamicModel3D::DynamicModel3D(AllegroFlare::Model3D* model_3d, ALLEGRO_BITMAP* model_3d_texture, AllegroFlare::Placement3D placement, AllegroFlare::Placement3D velocity)
   : AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::DynamicModel3D::TYPE)
   , model_3d(model_3d)
   , model_3d_texture(model_3d_texture)
   , placement(placement)
   , velocity(velocity)
{
}


DynamicModel3D::~DynamicModel3D()
{
}


void DynamicModel3D::set_model_3d(AllegroFlare::Model3D* model_3d)
{
   this->model_3d = model_3d;
}


void DynamicModel3D::set_model_3d_texture(ALLEGRO_BITMAP* model_3d_texture)
{
   this->model_3d_texture = model_3d_texture;
}


AllegroFlare::Model3D* DynamicModel3D::get_model_3d() const
{
   return model_3d;
}


ALLEGRO_BITMAP* DynamicModel3D::get_model_3d_texture() const
{
   return model_3d_texture;
}


AllegroFlare::Placement3D DynamicModel3D::get_placement() const
{
   return placement;
}


AllegroFlare::Placement3D DynamicModel3D::get_velocity() const
{
   return velocity;
}


AllegroFlare::Placement3D &DynamicModel3D::get_placement_ref()
{
   return placement;
}


AllegroFlare::Placement3D &DynamicModel3D::get_velocity_ref()
{
   return velocity;
}




} // namespace Entities
} // namespace DynamicEntityPipeline
} // namespace GraphicsPipelines
} // namespace AllegroFlare


