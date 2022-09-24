

#include <Wicked/Entities/Zones/Rectangle3D.hpp>




namespace Wicked
{
namespace Entities
{
namespace Zones
{


Rectangle3D::Rectangle3D(float x1, float y1, float z1, float x2, float y2, float z2)
   : Wicked::Entities::Zones::Base3D()
   , x1(x1)
   , y1(y1)
   , z1(z1)
   , x2(x2)
   , y2(y2)
   , z2(z2)
{
}


Rectangle3D::~Rectangle3D()
{
}


float Rectangle3D::get_x1() const
{
   return x1;
}


float Rectangle3D::get_y1() const
{
   return y1;
}


float Rectangle3D::get_z1() const
{
   return z1;
}


float Rectangle3D::get_x2() const
{
   return x2;
}


float Rectangle3D::get_y2() const
{
   return y2;
}


float Rectangle3D::get_z2() const
{
   return z2;
}


bool Rectangle3D::collides(AllegroFlare::vec3d point)
{
   if (point.x > x2) return false;
   if (point.x < x1) return false;
   if (point.y > y2) return false;
   if (point.y < y1) return false;
   if (point.z > z2) return false;
   if (point.z < z1) return false;
   return true;
}


} // namespace Zones
} // namespace Entities
} // namespace Wicked


