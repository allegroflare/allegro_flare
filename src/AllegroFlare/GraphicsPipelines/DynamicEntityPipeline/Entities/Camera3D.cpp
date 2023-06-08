

#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/Camera3D.hpp>




namespace AllegroFlare
{
namespace GraphicsPipelines
{
namespace DynamicEntityPipeline
{
namespace Entities
{


Camera3D::Camera3D(AllegroFlare::Camera3D camera_3d)
   : AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Camera3D::TYPE)
   , camera_3d(camera_3d)
{
}


Camera3D::~Camera3D()
{
}


AllegroFlare::Camera3D Camera3D::get_camera_3d() const
{
   return camera_3d;
}


AllegroFlare::Camera3D &Camera3D::get_camera_3d_ref()
{
   return camera_3d;
}




} // namespace Entities
} // namespace DynamicEntityPipeline
} // namespace GraphicsPipelines
} // namespace AllegroFlare


