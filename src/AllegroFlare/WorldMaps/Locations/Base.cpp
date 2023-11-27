

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


} // namespace Locations
} // namespace WorldMaps
} // namespace AllegroFlare


