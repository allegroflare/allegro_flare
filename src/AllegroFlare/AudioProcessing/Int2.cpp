

#include <AllegroFlare/AudioProcessing/Int2.hpp>




namespace AllegroFlare
{
namespace AudioProcessing
{


Int2::Int2()
   : x(0)
   , y(0)
{
}


Int2::~Int2()
{
}


void Int2::set_x(float x)
{
   this->x = x;
}


void Int2::set_y(float y)
{
   this->y = y;
}


float Int2::get_x() const
{
   return x;
}


float Int2::get_y() const
{
   return y;
}




} // namespace AudioProcessing
} // namespace AllegroFlare


