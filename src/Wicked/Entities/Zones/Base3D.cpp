

#include <Wicked/Entities/Zones/Base3D.hpp>




namespace Wicked
{
namespace Entities
{
namespace Zones
{


Base3D::Base3D()
   : Wicked::Entities::Base()
{
}


Base3D::~Base3D()
{
}


bool Base3D::collides(AllegroFlare::vec3d point)
{
   return false;
}


} // namespace Zones
} // namespace Entities
} // namespace Wicked


