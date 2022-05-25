

#include <AllegroFlare/Vec2B.hpp>



namespace AllegroFlare
{


Vec2B::Vec2B(bool x, bool y)
   : x(x)
   , y(y)
{
}


Vec2B::~Vec2B()
{
}


void Vec2B::set_x(bool x)
{
   this->x = x;
}


void Vec2B::set_y(bool y)
{
   this->y = y;
}


bool Vec2B::get_x()
{
   return x;
}


bool Vec2B::get_y()
{
   return y;
}


} // namespace AllegroFlare


