

#include <AllegroFlare/Vec2I.hpp>



namespace AllegroFlare
{


Vec2I::Vec2I(int x, int y)
   : x(x)
   , y(y)
{
}


Vec2I::~Vec2I()
{
}


void Vec2I::set_x(int x)
{
   this->x = x;
}


void Vec2I::set_y(int y)
{
   this->y = y;
}


int Vec2I::get_x()
{
   return x;
}


int Vec2I::get_y()
{
   return y;
}


} // namespace AllegroFlare


