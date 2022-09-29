

#include <AllegroFlare/Physics/Int2D.hpp>




namespace AllegroFlare
{
namespace Physics
{


Int2D::Int2D(int x, int y)
   : x(x)
   , y(y)
{
}


Int2D::~Int2D()
{
}


void Int2D::set_x(int x)
{
   this->x = x;
}


void Int2D::set_y(int y)
{
   this->y = y;
}


int Int2D::get_x() const
{
   return x;
}


int Int2D::get_y() const
{
   return y;
}


void Int2D::rotate()
{
   int s = x;
   x = y;
   y = s;
}


} // namespace Physics
} // namespace AllegroFlare


