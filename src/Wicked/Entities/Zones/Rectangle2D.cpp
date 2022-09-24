

#include <Wicked/Entities/Zones/Rectangle2D.hpp>




namespace Wicked
{
namespace Entities
{
namespace Zones
{


Rectangle2D::Rectangle2D(float x1, float y1, float x2, float y2)
   : Wicked::Entities::Zones::Base2D()
   , x1(x1)
   , y1(y1)
   , x2(x2)
   , y2(y2)
{
}


Rectangle2D::~Rectangle2D()
{
}


float Rectangle2D::get_x1() const
{
   return x1;
}


float Rectangle2D::get_y1() const
{
   return y1;
}


float Rectangle2D::get_x2() const
{
   return x2;
}


float Rectangle2D::get_y2() const
{
   return y2;
}


bool Rectangle2D::collides(AllegroFlare::vec2d point)
{
   if (point.x > x2) return false;
   if (point.x < x1) return false;
   if (point.y > y2) return false;
   if (point.y < y1) return false;
   return true;
}


} // namespace Zones
} // namespace Entities
} // namespace Wicked


