

#include <AllegroFlare/WorldMaps/Locations/Base.hpp>




namespace AllegroFlare
{
namespace WorldMaps
{
namespace Locations
{


Base::Base(std::string type)
   : type(type)
{
}


Base::~Base()
{
}


std::string Base::get_type() const
{
   return type;
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


