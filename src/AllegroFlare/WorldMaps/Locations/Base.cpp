

#include <AllegroFlare/WorldMaps/Locations/Base.hpp>




namespace AllegroFlare
{
namespace WorldMaps
{
namespace Locations
{


Base::Base(std::string type, float x, float y)
   : type(type)
   , x(x)
   , y(y)
{
}


Base::~Base()
{
}


void Base::set_x(float x)
{
   this->x = x;
}


void Base::set_y(float y)
{
   this->y = y;
}


std::string Base::get_type() const
{
   return type;
}


float Base::get_x() const
{
   return x;
}


float Base::get_y() const
{
   return y;
}


bool Base::collides(float x, float y)
{
   return false;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace Locations
} // namespace WorldMaps
} // namespace AllegroFlare


