

#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/StaticModel3D.hpp>




namespace AllegroFlare
{
namespace GraphicsPipelines
{
namespace DynamicEntityPipeline
{
namespace Entities
{


StaticModel3D::StaticModel3D(AllegroFlare::Placement3D placement)
   : AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::StaticModel3D::TYPE)
   , placement(placement)
{
}


StaticModel3D::~StaticModel3D()
{
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


