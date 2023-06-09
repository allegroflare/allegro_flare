

#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/StaticMultitextureModel3D.hpp>




namespace AllegroFlare
{
namespace GraphicsPipelines
{
namespace DynamicEntityPipeline
{
namespace Entities
{


StaticMultitextureModel3D::StaticMultitextureModel3D(AllegroFlare::MultitextureModel3D* multitexture_model_3d, ALLEGRO_BITMAP* multitexture_model_3d_texture_1, ALLEGRO_BITMAP* multitexture_model_3d_texture_2, AllegroFlare::Placement3D placement)
   : AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::StaticMultitextureModel3D::TYPE)
   , multitexture_model_3d(multitexture_model_3d)
   , multitexture_model_3d_texture_1(multitexture_model_3d_texture_1)
   , multitexture_model_3d_texture_2(multitexture_model_3d_texture_2)
   , placement(placement)
{
}


StaticMultitextureModel3D::~StaticMultitextureModel3D()
{
}


void StaticMultitextureModel3D::set_multitexture_model_3d(AllegroFlare::MultitextureModel3D* multitexture_model_3d)
{
   this->multitexture_model_3d = multitexture_model_3d;
}


void StaticMultitextureModel3D::set_multitexture_model_3d_texture_1(ALLEGRO_BITMAP* multitexture_model_3d_texture_1)
{
   this->multitexture_model_3d_texture_1 = multitexture_model_3d_texture_1;
}


void StaticMultitextureModel3D::set_multitexture_model_3d_texture_2(ALLEGRO_BITMAP* multitexture_model_3d_texture_2)
{
   this->multitexture_model_3d_texture_2 = multitexture_model_3d_texture_2;
}


AllegroFlare::MultitextureModel3D* StaticMultitextureModel3D::get_multitexture_model_3d() const
{
   return multitexture_model_3d;
}


ALLEGRO_BITMAP* StaticMultitextureModel3D::get_multitexture_model_3d_texture_1() const
{
   return multitexture_model_3d_texture_1;
}


ALLEGRO_BITMAP* StaticMultitextureModel3D::get_multitexture_model_3d_texture_2() const
{
   return multitexture_model_3d_texture_2;
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


