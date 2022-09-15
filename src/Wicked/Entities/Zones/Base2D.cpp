

#include <Wicked/Entities/Zones/Base2D.hpp>




namespace Wicked
{
namespace Entities
{
namespace Zones
{


Base2D::Base2D()
   : Wicked::Entities::Base()
{
}


Base2D::~Base2D()
{
}


bool Base2D::collides(AllegroFlare::vec2d point)
{
   // TODO: make this a pure virtual
   return false;
}


} // namespace Zones
} // namespace Entities
} // namespace Wicked


