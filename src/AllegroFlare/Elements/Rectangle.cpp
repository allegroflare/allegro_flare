

#include <AllegroFlare/Elements/Rectangle.hpp>




namespace AllegroFlare
{
namespace Elements
{


Rectangle::Rectangle()
   : x1(0.0f)
   , y1(0.0f)
   , x2(1.0f)
   , y2(1.0f)
{
}


Rectangle::~Rectangle()
{
}


float Rectangle::w()
{
   return x2-x1;
}

float Rectangle::h()
{
   return y2-y1;
}

void Rectangle::scale(float scale_x, float scale_y)
{
   x1 *= scale_x;
   y1 *= scale_y;
   x2 *= scale_x;
   y2 *= scale_y;
   return;
}

AllegroFlare::Elements::Rectangle Rectangle::build_xywh(float x, float y, float w, float h)
{
   AllegroFlare::Elements::Rectangle result;
   result.x1 = x;
   result.y1 = y;
   result.x2 = x + w;
   result.y2 = y + h;
   return result;
}

bool Rectangle::collides(AllegroFlare::Vec2D point)
{
   if (point.x > x2) return false;
   if (point.x < x1) return false;
   if (point.y > y2) return false;
   if (point.y < y1) return false;
   return true;
}


} // namespace Elements
} // namespace AllegroFlare


